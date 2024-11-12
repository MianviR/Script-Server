#include <array>
#include <iostream>
#include <boost/asio.hpp>
#include <ncurses.h>

using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2) 
	{
      std::cerr << "Usage: client <host>" << std::endl;
      return 1;
    }

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);
    tcp::resolver::results_type endpoints =
    resolver.resolve(argv[1], "1501");
    tcp::socket socket(io_context);
	boost::asio::connect(socket, endpoints);

	initscr();
    for (;;)
    {
		std::array<char, 1> ch;
		ch[0] = getch();
		print(ch[0]);
		boost::system::error_code ignored_error;
		boost::asio::write(socket, boost::asio::buffer(ch), ignored_error);
    }

	endwin();
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
