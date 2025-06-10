#include "utils.h"

int main()
{
	boost::asio::io_context ioc;
	tcp::resolver resolver(ioc);
	tcp::resolver::results_type endpoints = resolver.resolve(tcp::endpoint(boost::asio::ip::make_address("127.0.0.1"), 1025));
	tcp::socket socket(ioc);
	boost::asio::connect(socket, endpoints);
	boost::array<char, 128> buf;

	for (;;)
	{
		std::cin.getline(buf.data(), 128, '\n');
		if (strcmp(buf.data(), "end") == 0)
			break;
		
		socket.write_some(boost::asio::buffer(buf.data(), std::cin.gcount()));
	}

	return 0;	
}
