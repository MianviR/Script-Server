#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <fstream>
#include <filesystem>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

std::string read_file(const std::string& path) {
    std::ifstream file(path);
    if (!file) throw std::runtime_error("Не удалось открыть файл: " + path);
    return std::string((std::istreambuf_iterator<char>(file)),
                        std::istreambuf_iterator<char>());
}

void do_session(std::shared_ptr<tcp::socket> socket) {
    try {
        beast::flat_buffer buffer;

        http::request<http::string_body> req;
        http::read(*socket, buffer, req);

        http::response<http::string_body> res{http::status::ok, req.version()};
        res.set(http::field::server, "Boost.Beast");

        if (req.target() == "/") {
            std::string html = read_file("html/index.html");
            res.set(http::field::content_type, "text/html");
            res.body() = html;
        } else {
            res.result(http::status::not_found);
            res.set(http::field::content_type, "text/plain");
            res.body() = "404 Not Found";
        }

        res.prepare_payload();
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
