#include "client.h"

// void Client::connect(){
//   m_socket.connect(ip::tcp::endpoint(ip::address::from_string("localhost"),12345));
// }

void Client::send(ip::tcp::socket socket, std::string buf){
  socket.connect(ip::tcp::endpoint(ip::address::from_string(m_host), m_port));
  asio::write(socket, asio::buffer(buf));
}

// void Client::receive(ip::tcp::socket socket, std::string rec_buf){
//   asio::async_read(socket, rec_buf, asio::transfer_at_least(1), boost::bind(&Client::handler, this, asio::placeholders::error));
// }

// void Client::handler(const boost::system::error_code& err){
//   std::istream is(&m_rec_buf);
//   std::string data;
//   is >> data;
//   std::cout << data << std::endl;
//   receive();
// }

int Client::run(){
  try {
    ip::tcp::endpoint endpoint(ip::address::from_string(m_host), m_port);
    ip::tcp::socket socket(m_io);
    socket.connect(endpoint);
    std::string buf, old_buf;
    while(1)
      {
        usleep(wait_us);
        buf = getClip();
        if(buf != old_buf){
          asio::write(socket, asio::buffer(buf));
          old_buf = buf;
        }
      }
  }
  // catch (const boost::system::error_code& e)
  catch (const boost::exception& e)
    {
      std::cerr << "OMG!" << boost::diagnostic_information(e);
      // std::cout << e.what();
      return 1;
    }
  return 0;
}

int client(const std::string host, const unsigned int port) {
  try {
    boost::asio::io_service io;
    ip::tcp::endpoint endpoint(ip::address::from_string(host), port);
    ip::tcp::socket socket(io);
    socket.connect(endpoint);
    std::string buf, old_buf;
    while(1)
      {
        usleep(1000000);
        buf = getClip();
        if(buf != old_buf){
          asio::write(socket, asio::buffer(buf));
          old_buf = buf;
        }
      }
  }
  // catch (const boost::system::error_code& e)
  catch (const boost::exception& e)
    {
      std::cerr << "OMG!" << boost::diagnostic_information(e);
      // std::cout << e.what();
      return 1;
    }
  return 0;
}

