#include "utils.h"

class my_connection : public boost::enable_shared_from_this<my_connection>
{
	public:
	typedef boost::shared_ptr<my_connection> pointer;
	static size_t count;
	static pointer create(boost::asio::io_context& ioc)
	{
		return pointer(new my_connection(ioc));
	}
	my_connection(boost::asio::io_context& ioc) : socket_(ioc) {
		id = ++my_connection::count; 
		for (size_t i = 0; i < buf.size(); i++) 
			buf[i] = 0;
	}
	tcp::socket& socket() { return socket_; };
	void handle_server_connect() {
		std::cout << "User " << id << " connected" << std::endl;
		socket_.async_read_some(boost::asio::buffer(buf.data(), buf.size()),
			boost::bind(&my_connection::handle_server_accept,
					shared_from_this(),
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
	}
	void handle_server_disconnect() {
		std::cout << "User " << id << " disconnected" << std::endl;
		socket_.close();
	}
	void handle_server_accept(const boost::system::error_code& ec, size_t length) {
			if (!ec) {
				std::cout << "User " << id << ": " << buf.data();
				std::cout << std::endl;
				socket_.async_read_some(boost::asio::buffer(buf.data(), buf.size()),
					boost::bind(&my_connection::handle_server_accept,
						shared_from_this(),
						boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
			}
			else if (ec == boost::asio::error::eof) {
				handle_server_disconnect();
			}
			else {
				std::cout << ec.what() << std::endl;
			}
	}
	private:
	tcp::socket socket_;
	int id;
	boost::array<char, 128> buf;
};

size_t my_connection::count = 0;
