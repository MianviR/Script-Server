#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <array>
#include <thread>

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}

void beginConsoleConnection(tcp::socket& sock, boost::system::error_code err)
{
	for (;;)
	{
		std::array<char, 1> ch;
		sock.read_some(boost::asio::buffer(ch), err);
		if (err == boost::asio::error::eof)
			break;
		if (ch[0] == 4)
			break;
		std::cout << ch[0];
	}
}

void daytimeHandler(boost::asio::io_context& io_context,
					tcp::acceptor& acceptor)
{
	for (;;)
	{
		tcp::socket socket(io_context);
		acceptor.accept(socket);
		std::cout << "Daytime connected\n\n";

		std::string message = make_daytime_string();

		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(message), ignored_error);
		std::cout << "\nDaytime connection refused\n\n";
	}		
}

void consoleHandler(boost::asio::io_context& io_context,
					tcp::acceptor& acceptor)
{
	for (;;)
	{
		tcp::socket socket(io_context);
		acceptor.accept(socket);
		std::cout << "Console connected\n\n";

		boost::system::error_code error;
		beginConsoleConnection(socket, error);
		std::cout << "\nConsole connection refused\n\n";
	}
}

int main()
{
  try
  {
    boost::asio::io_context io_context;

    tcp::acceptor acceptor1(io_context, tcp::endpoint(tcp::v4(), 1500));
	tcp::acceptor acceptor2(io_context, tcp::endpoint(tcp::v4(), 1501));

	std::thread daytimeThread([&]{ daytimeHandler(io_context, acceptor1); });
	consoleHandler(io_context, acceptor2);
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
