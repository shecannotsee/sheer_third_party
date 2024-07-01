//
// Created by shecannotsee on 23-4-25.
//

#ifndef ASIO_TEST_ASIO_TEST_M3_SYNC_TCP_DEMO_H_
#define ASIO_TEST_ASIO_TEST_M3_SYNC_TCP_DEMO_H_

#include <ctime>
#include <vector>
#include <thread>
#include <asio.hpp>

namespace m3_sync_tcp_demo {

void main(int argc, char *argv[]) {
  int port = 0;

  auto client = [&](int argc,char* argv[]){
    try {
      asio::io_context io_context;
      using asio::ip::tcp;
      tcp::resolver resolver(io_context);
      // TODO:I don't know how to set.
      tcp::resolver::results_type endpoints = resolver.resolve("", "daytime");
      tcp::socket socket(io_context);
      port = socket.local_endpoint().port();
      sleep(2);
      asio::connect(socket, endpoints);
      for (;;) {
        std::vector<char> buf(128);
        asio::error_code error;

        size_t len = socket.read_some(asio::buffer(buf), error);
        // Server shutdown or disconnection
        if (error == asio::error::eof) {
          break; // Connection closed cleanly by peer.
        } else if (error) {
          throw asio::system_error(error); // Some other error.
        }

        std::cout.write(buf.data(), len);
      }
    }
    catch (std::exception &e) {
      std::cerr << e.what() << std::endl;
    }
  };

  auto server = [&](int argc,char* argv[]){
    try {
      asio::io_context io_context;
      using asio::ip::tcp;
      sleep(1);
      // TODO:I don't know how to set,
      tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), port));
      for (;;) {
        tcp::socket socket(io_context);
        acceptor.accept(socket);
        std::string message = ([]() -> std::string {
          using namespace std; // For time_t, time and ctime;
          time_t now = time(0);
          return ctime(&now);
        })();

        asio::error_code ignored_error;
        asio::write(socket, asio::buffer(message), ignored_error);
      }
    }
    catch (std::exception& e) {
      std::cerr << e.what() << std::endl;
    }
  };

  std::thread t1(client,argc,argv);
  std::thread t2(server,argc,argv);
  t1.join();
  t2.join();

};

};// namespace m3_sync_tcp_demo

#endif //ASIO_TEST_ASIO_TEST_M3_SYNC_TCP_DEMO_H_
