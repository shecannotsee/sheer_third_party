//
// Created by shecannotsee on 2023/2/17.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_9_CPP_SUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_9_CPP_SUB_H_

#include <iostream>
#include <string>
#include <utility>
#include <mqtt/async_client.h>


namespace method_9_cpp_sub {

class action_listener : public virtual mqtt::iaction_listener {
  std::string name_;
  void on_failure(const mqtt::token& tok) override {
    std::cout << name_ << " failure";
    if (tok.get_message_id() != 0)
      std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    std::cout << std::endl;
  };
  void on_success(const mqtt::token& tok) override {
    std::cout << name_ << " success";
    if (tok.get_message_id() != 0)
      std::cout << " for token: [" << tok.get_message_id() << "]" << std::endl;
    auto top = tok.get_topics();
    if (top && !top->empty())
      std::cout << "\ttoken topic: '" << (*top)[0] << "', ..." << std::endl;
    std::cout << std::endl;
  };
 public:
  action_listener(const std::string& name) : name_(name) {}
};

class callback : public virtual mqtt::callback,
                 public virtual mqtt::iaction_listener {
  std::string topic_;
  std::string client_id_;
  int number_of_reconnections_;
  mqtt::async_client& client_;
  // Options to use if we need to reconnect
  mqtt::connect_options& connect_options_;
  // An action listener to display the result of actions.
  action_listener sub_listener_;

  void reconnect() {
    std::this_thread::sleep_for(std::chrono::milliseconds(2500));
    try {
      client_.connect(connect_options_, nullptr, *this);
    }
    catch (const mqtt::exception& exc) {
      std::cerr << "Error: " << exc.what() << std::endl;
      exit(1);
    }
  }

  // Re-connection failure
  void on_failure(const mqtt::token& tok) override {
    std::cout << "Connection attempt failed" << std::endl;
    // 重连次数超过十次则程序退出
    if (++number_of_reconnections_ > 10) {
      exit(1);
    } else {
      reconnect();
    }
  }

  // (Re)connection success
  // Either this or connected() can be used for callbacks.
  void on_success(const mqtt::token& tok) override {}

  // (Re)connection success
  void connected(const std::string& cause) override {
    std::cout << "Connection success\n";
    std::cout << "Subscribing to topic '" << topic_ << "'\n"
              << "\tfor client " << client_id_
              << " using QoS[" << /*QOS*/1 << "]\n";
    client_.subscribe(topic_, /*QOS*/1, nullptr, sub_listener_);
  };

  // Callback for when the connection is lost.
  // This will initiate the attempt to manually reconnect.
  void connection_lost(const std::string& cause) override {
    std::cout << "Connection lost.\n";
    if (!cause.empty())
      std::cout << "cause:[" << cause << "]\n";

    std::cout << "Reconnecting...\n";
    number_of_reconnections_ = 0;
    reconnect();
  }

  // Callback for when a message arrives.
  void message_arrived(mqtt::const_message_ptr msg) override {
    std::cout << "Message arrived.\n";
    std::cout << "topic:[" << msg->get_topic() << "]\n";
    std::cout << "payload:[" << msg->to_string() << "]\n";
  }

  void delivery_complete(mqtt::delivery_token_ptr token) override {}

 public:
  callback(mqtt::async_client& client, mqtt::connect_options& connect_options,std::string topic, std::string client_id)
      : number_of_reconnections_(0),
        client_(client),
        connect_options_(connect_options),
        sub_listener_("Subscription"),
        topic_(std::move(topic)),
        client_id_(std::move(client_id)) {}
};

void main() {
  std::string server_url  = "tcp://localhost:1883";
  std::string client_id   = "ssl_sub";
  std::string topic       = "hello";

  mqtt::async_client client(server_url,client_id);
  mqtt::connect_options connect_options;
  connect_options.set_clean_session(false);

  callback cb(client, connect_options,topic,client_id);
  client.set_callback(cb);

  // Start the connection.
  // When completed, the callback will subscribe to topic.
  try {
    std::cout << "Connecting to the MQTT server..." << std::flush;
    client.connect(connect_options, nullptr, cb);
  }
  catch (const mqtt::exception& exc) {
    std::cerr << "ERROR: Unable to connect to MQTT server:["
              << server_url << "][" << exc << "]\n";
    return ;
  }

  // Just block till user tells us to quit.
  while (std::tolower(std::cin.get()) != 'q')
    ;

  // Disconnect
  try {
    std::cout << "\nDisconnecting from the MQTT server..." << std::flush;
    client.disconnect()->wait();
    std::cout << "OK" << std::endl;
  }
  catch (const mqtt::exception& exc) {
    std::cerr << exc << std::endl;
    return ;
  }

};

};// namespace method_9_cpp_sub {

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_9_CPP_SUB_H_
