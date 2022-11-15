#include <iostream>
#include <boost/asio.hpp>

void print(const boost::system::error_code&)
{
	std::cout << "xxxx" << std::endl;
}

int main()
{
	std::cout << (sizeof(long) > sizeof(int));
	boost::asio::io_context io;
	boost::asio::steady_timer t(io, boost::asio::chrono::seconds(5));
	t.async_wait(print);
	io.run();
}