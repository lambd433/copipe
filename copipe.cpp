//
// assignment
// -implementation of client command (last, get, push, insert)
// -security
// - ore ore protocol(ver, date, ip, cont)
// - event handler

// -for Linux
// -daemon
//#include <X11/Xlib.h>

#include "server.h"
#include "client.h"

#include <iostream>
int main(int argc, char **argv)
{
  int result = 0;
  bool flag_server = 0;
  std::string host;
  unsigned int port = SERVER_PORT;
  while((result = getopt(argc, argv, "c:p:s")) != -1)
    {
      switch(result){
      case 'c': //client (host to connect)
        host = optarg;
        break;
      case 's': //server
        flag_server = 1;
        host = "127.0.0.1";
        break;
      case 'p': //port
        port = std::stoi(optarg);
        break;
      case ':':
        break;
      case '?':
        std::cerr << "Usage: " << argv[0] << std::endl;
        std::exit(1);
      default:
        std::cerr << "Usage: " << argv[0] << std::endl;
        std::exit(1);
      }
      
    }
  std::cout << "flag_server " << flag_server << " host " << host << " port " << port << std::endl;
  if(flag_server) server(host, port);
  else client(host, port);
  return 0;
}
