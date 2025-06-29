#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/http/impl/fields.hpp>
#include <boost/beast/http/message_fwd.hpp>
#include <boost/beast/http/parser_fwd.hpp>
#include <boost/beast/http/serializer.hpp>
#include <boost/beast/http/string_body_fwd.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind/bind.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/cxx11/any_of.hpp>
#include <boost/any.hpp>
#include <inja/template.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <fstream>
#include <map>
#include <boost/filesystem.hpp>
#include <iterator>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <nlohmann/json.hpp>
#include <inja/inja.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using json = nlohmann::json;

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть файл: " + path);
    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

bool addScript(const char* scrName, const char* scrText) {
	char filePath[256];
	sprintf(filePath, "scripts/%s", scrName);
	
	int fd = open(filePath, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0) {
		std::cerr << "addScript: Error open " << scrName << std::endl;
		return 0;
	}

	write(fd, scrText, strlen(scrText));
	close(fd);

	return 1;
}

void renameScript(const char* scrName, const char* scrNameNew) {
	char filePath[256];
	char newFilePath[256];
	sprintf(filePath, "scripts/%s", scrName);
	sprintf(newFilePath, "scripts/%s", scrNameNew);
	
	//TODO
}

std::vector<std::string> getDirScriptsFiles() {
	using namespace boost::filesystem;

	char scriptsPath[128];
	char cwd[128];
	getcwd(cwd, 128);
	sprintf(scriptsPath, "%s/%s", cwd, "scripts");
	path p = scriptsPath;
	std::vector<std::string> ret(0);
	if (!exists(p) || is_regular_file(p)) {
		return ret;
	}

	for (const auto& entry : directory_iterator(scriptsPath)) {
		if (is_regular_file(entry)) {
			std::string buf = entry.path().string();
			size_t pos = 0;
			pos = buf.find('/');
			while ((pos = buf.find('/', 0)) != std::string::npos) {
				buf = buf.substr(pos+1);
			}
			ret.push_back(buf);
		}
	}
	
	return ret;
}

void runScript(const char* name) {
	int pid = fork();	
	switch (pid) {
		case -1: std::cerr << "runScript: error fork\n"; break;
		case 0: {
			int fd = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd < 0) {
				std::cerr << "runScript: Error open output.txt\n";
				return;
			}
	
			char path[128];
			sprintf(path, "scripts/%s", name);

			dup2(fd, STDOUT_FILENO);
			dup2(fd, STDERR_FILENO);
			close(fd);

			execl("/bin/python3", "/bin/python3", path);
			break;
		}
		default: 
			sleep(2);	
			break;
	}
}

void deleteScript(const char* name) {
	char path[128];
	sprintf(path, "scripts/%s", name);
	std::remove(path);
}



void get_query(http::request<http::string_body>& req, std::string* query = nullptr, std::string* path = nullptr) {
	std::string uri = req.target();
	std::size_t pos = uri.find('?');
	if (pos != std::string::npos) {
		if (path != NULL)
			*path = uri.substr(0, pos);
		if (query != NULL)
			*query = uri.substr(pos + 1);
	}
	else if (path != NULL)
		*path = uri;
}

boost::shared_ptr<std::map<std::string, std::string>> splitGetParams(std::string& query) {
	auto params = boost::make_shared<std::map<std::string, std::string>>();
	std::size_t start = 0;

	while (start < query.length()) {
		std::size_t end = query.find('&', start);
		if (end == std::string::npos) end = query.length();

		std::size_t eq = query.find('=', start);
		if (eq != std::string::npos && eq < end) {
			std::string key = query.substr(start, eq - start);
			std::string val = query.substr(eq + 1, end - eq - 1);
			(*params)[key] = val;
		}

		start = end + 1;
	}
	return params;
}

boost::shared_ptr<std::map<std::string, std::string>> splitPostParams(std::string& query) {
	auto params = boost::make_shared<std::map<std::string, std::string>>();
	auto pos = query.find("=");
	json j = json::parse(query.substr(pos+1));

	for (auto& [key, value] : j.items()) {
		(*params)[key] = value.get<std::string>();	
	}

	return params;
}

void redirect_to(std::string path, http::request<http::string_body>& req, http::response<http::string_body>& res) {
	res.result(http::status::found);
	res.set(http::field::location, path);
	res.set(http::field::server, "Script server");
	res.set(http::field::content_type, "text/plain");
	res.keep_alive(req.keep_alive());
	res.body() = "redirecting to /";	
} 

void handle_request(http::request<http::string_body>& req, http::response<http::string_body>& res) {
		res.result(http::status::ok);
		res.version(req.version());
        res.set(http::field::server, "Boost.Beast");
		std::string path, query;
		get_query(req, &query, &path);
		auto params = splitGetParams(query);
		inja::Environment env;
		inja::json data;
		inja::Template temp;

        if (path == "/") {
			std::string html;
			temp = env.parse_template("html/index.html");
			data["files"] = getDirScriptsFiles();
			html = env.render(temp, data);
            res.set(http::field::content_type, "text/html");
            res.body() = html;
		} else if (path == "/newScript" && req.method() == http::verb::get) {
			data["picked"] = false;
			temp = env.parse_template("html/newScript.html");
			res.set(http::field::content_type, "text/html");
			res.body() = env.render(temp, data);
		} else if (path == "/newScript" && req.method() == http::verb::post) { 
			temp = env.parse_template("html/newScript.html");
			res.set(http::field::content_type, "text/html");
			params = splitPostParams(req.body());
			auto iterName = params->find("scrName");
			auto iterText = params->find("scrText");
			std::string scrText = "";
			if (iterText != params->end())
				scrText = iterText->second;
			
			if (iterName != params->end()) {
				auto files = getDirScriptsFiles();
				if (!boost::algorithm::any_of(files.begin(), files.end(), [iterName](std::string& s) {
					return s == iterName->second;
				})) {
					addScript(iterName->second.c_str(), scrText.c_str());
					redirect_to("/", req, res);
				}
				else {
					res.result(http::status::bad_request);
					data["scrName"] = iterName->second;
					data["scrText"] = scrText;
					data["picked"] = true;
					res.body() = env.render(temp, data);
				}
			}
		} else if (path == "/scriptResult") {
			auto iter = params->find("id");		
			if (iter != params->end()) {
				auto files = getDirScriptsFiles();
				runScript(files[std::stoi(iter->second)].c_str());
				std::string html = read_file("output.txt");
				res.set(http::field::content_type, "text/plain");
				res.body() = html;
			}
		} else if (path == "/scriptDelete") {
			auto iter = params->find("id");
			if (iter != params->end()) {
				auto files = getDirScriptsFiles();
				deleteScript(files[std::stoi(iter->second)].c_str());
				redirect_to("/", req, res);
			}
		} else if (path == "/scriptEdit" && req.method() == http::verb::get) {
			std::string html = "";
			inja::Template temp = env.parse_template("html/editScript.html");
			auto files = getDirScriptsFiles();
			auto iter = params->find("id");
			std::string fileName = "";
			std::string scrText = "";
			if (iter != params->end()) {
				fileName = files[stoi(iter->second)];
				scrText = read_file("scripts/"+fileName);
				std::cout << fileName << '\n' << scrText << "\n\n";
				data["scrName"] = fileName;
				data["scrText"] = scrText;
			}
			html = env.render(temp, data);
			res.set(http::field::content_type, "text/html");
			res.body() = html;	
		} else {
            res.result(http::status::not_found);
            res.set(http::field::content_type, "text/plain");
            res.body() = "404 Not Found";
        }

        res.prepare_payload();
}

void do_session(std::shared_ptr<tcp::socket> socket) {
    try {
        beast::flat_buffer buffer;

        http::request<http::string_body> req;
        http::read(*socket, buffer, req);
		http::response<http::string_body> res;
		handle_request(req, res);
        http::write(*socket, res);
    } catch (const std::exception& e) {
        std::cerr << "Session error: " << e.what() << std::endl;
    }
}

int main() {
    try {
        net::io_context ioc;
        tcp::acceptor acceptor{ioc, {tcp::v4(), 8080}};
        std::cout << "Server is listening on http://localhost:8080\n";

        for (;;) {
            auto socket = std::make_shared<tcp::socket>(ioc);
            acceptor.accept(*socket);
            std::thread{boost::bind(&do_session, socket)}.detach();
        }
    } catch (std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << "\n";
    }
}
