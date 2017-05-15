#include <iostream>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/system/error_code.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio/basic_deadline_timer.hpp>

boost::asio::io_service *ioPtr = NULL;
boost::asio::deadline_timer *timerPtr = NULL;
unsigned int interval_sec = 1;

int print( const boost::system::error_code& /*e*/ )
{
    std::cout << "Hello World!!!" << std::endl;
}

void run()
{
    if ( ioPtr )
    {
        ioPtr->run();
    }else
    {
        std::cout << "ioPtr is null!!!" << std::endl;
    }
}

void setTimer()
{
    if ( timerPtr )
    {
        timerPtr->expires_from_now( boost::posix_time::seconds( interval_sec ) );
    }else
    {
        std::cout << "timerPtr is null!!!" << std::endl;
    }
}

void crontab( const boost::system::error_code& e )
{
    print(e);
    setTimer();
    if ( timerPtr )
    {
        timerPtr->async_wait( boost::bind( crontab, boost::asio::placeholders::error ) );
    }else
    {
        std::cout << "timerPtr is null!!!" << std::endl;
    }
}

int main()
{
    ioPtr = new boost::asio::io_service();
    timerPtr = new boost::asio::deadline_timer( *ioPtr, boost::posix_time::seconds( interval_sec ) );
    timerPtr->async_wait( boost::bind( crontab, boost::asio::placeholders::error ) );
    boost::thread *threadPtr = new boost::thread( boost::bind( run ) );
    while (1)
    {
        sleep(10);
    }
    threadPtr->interrupt();
    threadPtr->join();
    delete threadPtr;
    delete timerPtr;
    delete ioPtr;
    return 0;
}
