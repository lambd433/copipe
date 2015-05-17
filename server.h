#include "network.h"
#include "clip.h"

#ifndef SERVER_H
#define SERVER_H
#define SERVER_PORT 12344

class Server {
 private:
  const unsigned int wait_us = 200000;
  asio::io_service m_io;
  std::string m_os;
  std::string m_host;
  unsigned int m_port;
  //ip::tcp::endpoint m_endpoint(ip::address::from_string(m_host), m_port);
  //ip::tcp::socket m_socket(m_io);
  void handler(const boost::system::error_code& err);
 public:
 Server(std::string host, unsigned int port): m_host(host), m_port(port){}
  ~Server(){}
  //  void connect();
  int run();
};

int server(const std::string host, const unsigned int port);
#endif

