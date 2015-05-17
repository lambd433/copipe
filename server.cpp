#include "server.h"

int Server::run() {
  ip::tcp::socket socket(m_io);
  ip::tcp::endpoint endpoint(ip::tcp::v4(), m_port);
  ip::tcp::acceptor acceptor(m_io, endpoint);
  acceptor.accept(socket);
  std::string buf;
  while(1)
    {
      try {
        asio::streambuf rec_buf;
        std::string buf;
        std::string old_buf;
        boost::system::error_code err;
        asio::read(socket, rec_buf, asio::transfer_at_least(1), err);
        if(err && err != asio::error::eof)
          std::cout << " Failed to receive: " << err.message() << std::endl;
        buf = asio::buffer_cast<const char *>(rec_buf.data());
        if( buf != old_buf){
          std::cout << &rec_buf << std::endl;
          old_buf = buf;
        }
        usleep(wait_us);
      } catch (const boost::exception& e){
        std::cerr << "OMG!" << boost::diagnostic_information(e);
        // std::cout << e.what();
        return 1;
      }
    }
  return 0;
}

int server(const std::string host, const unsigned int port) {
  asio::io_service io;
  ip::tcp::socket socket(io);

  //  ip::address::from_string("")
  ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
  ip::tcp::acceptor acceptor(io, endpoint);
  acceptor.accept(socket);
  std::string buf;
  while(1)
    {
      asio::streambuf rec_buf;
      std::string buf;
      std::string old_buf;
      boost::system::error_code err;
      asio::read(socket, rec_buf, asio::transfer_at_least(1), err);
      if(err && err != asio::error::eof)
        std::cout << " Failed to receive: " << err.message() << std::endl;
      buf = asio::buffer_cast<const char *>(rec_buf.data());
      if( buf != old_buf){
        std::cout << &rec_buf << std::endl;
        old_buf = buf;
      }
      usleep(1000000);
    }
  return 0;
}

// int aserver(const std::string host, const unsigned int port) {
//   asio::io_service io;
//   ip::tcp::socket socket(io);

//   //  ip::address::from_string("")
//   ip::tcp::endpoint endpoint(ip::tcp::v4(), port);
//   ip::tcp::acceptor acceptor(io, endpoint);
//   acceptor.accept(socket);
//   std::string buf;
//   asio::streambuf rec_buf;
//   std::string old_buf;
//   boost::system::error_code err;

//   asio::deadline_timer t(io, boost::posix_time::seconds(1));
//   t.async_wait(boost::bind(print, boost::asio::placeholders::error, &t));
//   io.run();
//   asio::read(socket, rec_buf, asio::transfer_at_least(1), err);
//   if(err && err != asio::error::eof)
//     std::cout << " Failed to receive: " << err.message() << std::endl;
//   buf = asio::buffer_cast<const char *>(rec_buf.data());
//   if( buf != old_buf){
//     std::cout << &rec_buf << std::endl;
//     old_buf = buf;
//   }
//   return 0;
// }

void handler(const boost::system::error_code& err)
{}
