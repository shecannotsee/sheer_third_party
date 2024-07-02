//
// Created by shecannotsee on 2022/9/26.
//
#include <iostream>

#include <server_http.hpp>

using std::shared_ptr;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;

int main() {
  HttpServer server;
  server.config.port = 9999;

  // register interface
  // how to parse like
  // http://127.0.0.1:9999/info?id=16&pageSize=5&file_path=/home/shecannotsee/Desktop/AllCode/3rd/boost_1_79_0
  server.resource["^/info$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    std::stringstream stream;
    stream << "[1]"   << request->remote_endpoint().address().to_string()
           << "\n[2]" << request->remote_endpoint().port();

    stream << "\n[3]" << request->method
           << "\n[4]" << request->path
           << "\n[5]" << request->http_version;

    stream << "\n[6]\n";
    auto query_fields = request->parse_query_string();
    for(auto &field : query_fields)
      stream << field.first << ": " << field.second << "\n";
    /*
     * file_path: /home/shecannotsee/Desktop/AllCode/3rd/boost_1_79_0
     * pageSize: 5
     * id: 16
     * */

    stream << "\n[7]\n";
    for(auto &field : request->header)
      stream << field.first << ": " << field.second << "\n";

    response->write(stream);
  };

  server.resource["^/match/([0-9]+)$"]["GET"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    response->write(request->path_match[1].str());
  };

  // server start
  std::thread server_thread([&server]() {
    server.start();
  });
  server_thread.join();

  std::cout<<"1\n";
  return 0;
};

