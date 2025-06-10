#include "utils.h"
#include "my_connection.h"
#include <threads.h>

class my_server
{
	public:
	my_server(boost::asio::io_context& ioc, size_t port)
	: ioc_(ioc),
	  acceptor_(ioc_, tcp::endpoint(tcp::v4(), port))
	{
		start_accept();	
	}
	private:
	boost::asio::io_context& ioc_;
	tcp::acceptor acceptor_;
	void start_accept()
	{
		my_connection::pointer new_connection =
			my_connection::create(ioc_);
		acceptor_.async_accept(new_connection->socket(), boost::bind(&my_server::handle_accept, this, new_connection, boost::asio::placeholders::error));
	}
	void handle_accept(my_connection::pointer con, const boost::system::error_code& error)
	{
		if (!error) {
			con->handle_server_connect();
		}

		start_accept();
	}
};

int main()
{
	try
	{
		boost::asio::io_context ioc;
		my_server server(ioc, 1025);
		
		ioc.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	return 0;
}
