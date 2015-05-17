#include "network.h"
#include "clip.h"

#define CLIENT_PORT 12345

#ifndef CLIENT_H
#define CLIENT_H



int client(const std::string host, const unsigned int port);

class Client {
 private:
  const unsigned int wait_us = 200000;
  asio::io_service m_io;
  std::string m_os;
  std::string m_host;
  unsigned int m_port;
  std::string m_client_ip;
  std::string m_client_port;

  //ip::tcp::endpoint m_endpoint(ip::address::from_string(m_host), m_port);
  //ip::tcp::socket m_socket(m_io);
  void handler(const boost::system::error_code& err);
 public:
 Client(std::string host, unsigned int port): m_host(host), m_port(port){}
  ~Client(){}
  //  void connect();
  void receive(ip::tcp::socket socket, std::string rec_buf);
  int run();
  void send(ip::tcp::socket socket, std::string buf);
};

#endif
