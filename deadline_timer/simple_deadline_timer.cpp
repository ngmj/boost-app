#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

//int print( const boost::system::err_code &ec )
int print( const boost::system::error_code& /*e*/ )
{
    std::cout << "Hello World!!!" << std::endl;
}

int main()
{
    boost::asio::io_service io;
    boost::asio::deadline_timer t( io, boost::posix_time::seconds(5) );
    t.async_wait( boost::bind( print, boost::asio::placeholders::error ) );
    io.run();
}
