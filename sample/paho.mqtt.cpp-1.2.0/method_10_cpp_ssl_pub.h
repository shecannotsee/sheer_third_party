//
// Created by shecannotsee on 2023/2/17.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_10_CPP_SSL_PUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_10_CPP_SSL_PUB_H_

#include <iostream>
#include <fstream>// read ssl key from file
#include <unistd.h>
#include <mqtt/async_client.h>

namespace method_10_cpp_ssl_pub {

// 重写回调
class callback : public virtual mqtt::callback {
 public:
  void connection_lost(const std::string& cause) override {
    std::cout << "Connection lost.\n";
    if (!cause.empty())
      std::cout << "cause:[" << cause << "]\n";
  };
  void delivery_complete(mqtt::delivery_token_ptr tok) override {
    std::cout << "Delivery complete for token:["
              << (tok ? tok->get_message_id() : -1) << "]\n";
  }
};

void main() {
  std::string server_url  = "tcp://localhost:1883";
  std::string client_id   = "ssl_pub";
  std::string topic       = "hello";
  std::string message     = "hello world";


  mqtt::async_client client(server_url,client_id);
  callback cb;
  client.set_callback(cb);

  std::string KEY_STORE   = "client.pem";
  std::string TRUST_STORE = "test-root-ca.crt";
  /* ssl file get */
  if (false) {
    std::ifstream tstore(TRUST_STORE);
    if (!tstore) {
      std::cerr << "The trust store file does not exist: " << TRUST_STORE << std::endl;
      std::cerr << "  Get a copy from \"paho.mqtt.c/test/ssl/test-root-ca.crt\"" << std::endl;;
      return ;
    };

    std::ifstream kstore(KEY_STORE);
    if (!kstore) {
      std::cerr << "The key store file does not exist: " << KEY_STORE << std::endl;
      std::cerr << "  Get a copy from \"paho.mqtt.c/test/ssl/client.pem\"" << std::endl;
      return ;
    };
  };
  mqtt::ssl_options sslopts = mqtt::ssl_options_builder()
      .trust_store(TRUST_STORE)
      .key_store(KEY_STORE)
      .error_handler([](const std::string& msg) {
        std::cerr << "SSL Error: " << msg << std::endl;
      })
      .finalize();

  mqtt::message will_message = mqtt::message("events/disconnect", "Last will and testament.", /*QOS*/1, true);

  mqtt::connect_options connect_options = mqtt::connect_options_builder()
      .user_name("testuser")
      .password("testpassword")
      .will(std::move(will_message)) // 添加willmsg
//                                          .ssl(std::move(sslopts)) // 添加ssl信息
      .finalize();


  try {
    /* Connect using SSL/TLS */ {
      std::cout << "Connecting...\n";
      mqtt::token_ptr connect_token = client.connect(connect_options);
      std::cout << "Waiting for the connection...\n";
      connect_token->wait();
      std::cout << "Done\n";
    }

    while (true) {
      /* Send a message */ {
        std::cout << "Sending message...\n";
        auto msg = mqtt::make_message(topic, message, /*QOS*/1, false);
        client.publish(msg)->wait_for(10000/*ms*/);
        std::cout << "Done\n";
      };
      sleep(10);
    }

    /* Disconnect */ {
      std::cout << "Disconnecting...\n";
      client.disconnect()->wait();
      std::cout << "Done\n";
    }
  }
  catch (const mqtt::exception& exc) {
    std::cerr << exc.what() << std::endl;
    return ;
  }

};


};// namespace method_10_cpp_ssl_pub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_10_CPP_SSL_PUB_H_
