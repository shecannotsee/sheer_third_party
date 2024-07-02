//
// Created by shecannotsee on 2023/2/22.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_12_CPP_PUB_SUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_12_CPP_PUB_SUB_H_

#include <iostream>
#include <string>
#include <vector>
#include <future>
#include <atomic>
#include <mqtt/async_client.h>

namespace method_12_cpp_pub_sub {

using UpCallback = std::function<void(const std::string& topic, const std::string& message)>;

class mqttCallbacks : public virtual mqtt::callback,
                      public virtual mqtt::iaction_listener {
 public:
  mqttCallbacks(mqtt::async_client& client, mqtt::connect_options& connect_options,UpCallback cb)
      : client_(client),
        connect_options_(connect_options),
        callback_(cb) {};
 private:
  mqtt::async_client& client_;
  mqtt::connect_options& connect_options_;
  UpCallback callback_;
 public:

  void reconnect() {
    do {
      try {
        client_.connect(connect_options_, nullptr, *this);
        std::cout << "Reconnect success.\n";
      }
      catch (const mqtt::exception &exc) {
        std::cout << "reconnect error: [" << exc.what() << "]\n";
        sleep(3);
      }
    } while (true);
  };

  // Re-connection failure
  void on_failure(const mqtt::token& tok) override {
    std::cout << "Connection attempt failed" << std::endl;
    reconnect();
  };

  // (Re)connection success
  // Either this or connected() can be used for callbacks.
  void on_success(const mqtt::token& tok) override {
    std::cout<< "[on_success]Connect to mqtt server success.\n";
  };

  // (Re)connection success
  void connected(const std::string& cause) override {
    std::cout<< "[connected]Connect to mqtt server success.\n";
  };

  // Callback for when the connection is lost.
  // This will initiate the attempt to manually reconnect.
  void connection_lost(const std::string& cause) override {
    std::cout << "Connection lost.\n";
    if (!cause.empty()) {
      std::cout << "cause:[" << cause << "]\n";
    }
    std::cout << "Start to reconnecting...\n";
    reconnect();
  };

  // Callback for when a message arrives.
  void message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message arrived:";
    std::cout << msg->get_topic();
    std::cout << "[" << msg->to_string() << "]\n";
    if (callback_) {
      std::string topic   = std::string(msg->get_topic());
      std::string payload = std::string(msg->to_string());
      callback_(topic,payload);
    }
  };

  // Callback for send message suucess
  void delivery_complete(mqtt::delivery_token_ptr token) override {
    int tokenNum = (token ? token->get_message_id() : -1);
    std::cout << "Delivery complete for token:[" << tokenNum << "]\n";
  };

};// class callback

void main() {
  std::vector<std::string> topics{"topic_1","topic_2","topic_3"};
  std::vector<int>         QOS   {1,1,1};

  std::string serverAddress = "tcp://localhost:1883";
  std::string clientId = "method12_client";

  mqtt::async_client client(serverAddress,clientId);


  // set connect options
  bool set_ssl = false;
  mqtt::ssl_options ssl_options{};/* set */ {
    std::string KEY_STORE   = "client.pem";
    std::string TRUST_STORE = "test-root-ca.crt";
    if (set_ssl) {
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
    ssl_options.set_trust_store(TRUST_STORE);
    ssl_options.set_key_store(KEY_STORE);
    ssl_options.set_error_handler([](const std::string& msg) {
      std::cerr << "SSL Error: " << msg << std::endl;
    });
  };
  mqtt::connect_options connect_options{};/* set */ {
    connect_options.set_user_name("admin");
    connect_options.set_password("123456");
    connect_options.set_clean_session(true);
    if (set_ssl) connect_options.set_ssl(std::move(ssl_options));
    mqtt::message will_message = mqtt::message("/quit","Last will and testament",/*QOS*/1, false);
    connect_options.set_will_message(std::move(will_message));
  }

  std::atomic<bool> connect_success {false};

  // connect(block)
connect:
  try {
    bool use_block = true;
    if (use_block) {
      mqtt::token_ptr connect_token = client.connect(connect_options);
      connect_token->wait();// block to connect until success
    }
    else {
      client.connect(connect_options);
    }
    connect_success = true;
  }
  catch (const mqtt::exception& exc) {
    std::cout << "connect error:" << exc.what() << std::endl;
    sleep(1);
    goto connect;
  };

  // set callback
  UpCallback cssCallback = [](std::string topic,std::string payload){
    std::cout<<"cssCallback:"<<topic<<"["<<payload<<"]\n";
  };
  mqttCallbacks cb(client,connect_options, cssCallback);
  client.set_callback(cb);

  // subscribe
  std::async(std::launch::async,[&](){
    for (int i=0;i<topics.size();i++) {
      client.subscribe(topics[i],QOS[i]);
    }
  });

  // publish
  std::async(std::launch::async,[&](){
    for (int i=0;i<topics.size();i++) {
      client.publish(topics[i],std::to_string(i+1),QOS[i], false);
      sleep(1);
    }
  });

  // disconnect
  try {
    client.disconnect()->wait();
  }
  catch (const mqtt::exception& exc) {
    std::cout << "Disconnect error :" << exc.what() << std::endl;
  };

  sleep(100);


};

};// namespace method_12_cpp_pub_sub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_12_CPP_PUB_SUB_H_
