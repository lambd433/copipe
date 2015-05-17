#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <memory>
#include <sys/wait.h>
#include <sys/time.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/exception/diagnostic_information.hpp> 
#include <boost/exception_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#ifndef NETWORK_H
#define NETWORK_H
namespace asio = boost::asio; 
namespace ip = asio::ip;
#endif
