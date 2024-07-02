//
// Created by shecannotsee on 2023/2/17.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_11_CPP_PUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_11_CPP_PUB_H_

#include <iostream>
#include <string>
#include <chrono>
#include <atomic>
#include <mutex>
#include <mqtt/async_client.h>

namespace method_11_cpp_pub {

using ::std::string;
using ::std::cout;
using ::std::endl;

class callback : public virtual mqtt::callback {
 public:
  // 连接断开
  void connection_lost(const string& cause) override {
    cout << "Connection lost.\n" << endl;
    if (!cause.empty()) {
      cout << "\tcause: " << cause << endl;
    }
  };
  // 发送消息成功
  void delivery_complete(mqtt::delivery_token_ptr tok) override {
    cout << "send message complete,token:["<< (tok ? tok->get_message_id() : -1) << "]\n";
  }
};
class action_listener : public virtual mqtt::iaction_listener {
 protected:
  void on_success(const mqtt::token& tok) override {
    cout << "Listener success for token:["<< tok.get_message_id() << "]\n";
  };
  void on_failure(const mqtt::token& tok) override {
    cout << "Listener failure for token:["<< tok.get_message_id() << "]\n";
  }
};
class delivery_action_listener : public action_listener {
  std::atomic<bool> done_;
  void on_failure(const mqtt::token& tok) override {
    action_listener::on_failure(tok);
    done_ = true;
  }
  void on_success(const mqtt::token& tok) override {
    action_listener::on_success(tok);
    done_ = true;
  }
 public:
  delivery_action_listener() : done_(false) {};
  bool is_done() const { return done_; };
};

void main() {
  string server_url   = "tcp://localhost:1883";
  string client_id    = "async_client_pub";
  string topic        = "topic_b";
  string message1     = "1 message";
  string message2     = "2 message";
  string message3     = "3 message";
  string message4     = "4 message";
  const auto time_out = std::chrono::seconds(10);
  std::mutex mtx;

  mqtt::async_client client(server_url,client_id);
  callback cb;// 需要保持该类生命周期和async_client相同
  client.set_callback(cb);

  try {
    /* connect*/ {
      cout << "Connecting...\n" << endl;
      mqtt::connect_options connOpts = mqtt::connect_options_builder()
          .clean_session()
          .will(mqtt::message(topic, "Last will and testament.", /*QOS*/1))
          .finalize();
      mqtt::token_ptr connect_token = client.connect(connOpts);
      cout << "Waiting for the connection(block)..." << endl;
      connect_token->wait();// 等待连接完成
      cout << "success to connect.\n" << endl;
    }

    /* First use a message pointer. */ {
      cout << "\nsimple sending..." << endl;
      mqtt::message_ptr publish_msg = mqtt::make_message(topic, message1.c_str());// 组装消息
      publish_msg->set_qos(/*QOS*/1);// 设置消息等级
      client.publish(publish_msg)->wait_for(time_out);// 传入等待消息发送的时间,超时则返回false
      cout << "done.\n" << endl;
    };

    /* Now try with itemized publish,itemized publish 允许将大于 MQTTAsync_maxBufferSize 的消息分成多个消息块（chunks）发送 */ {
      cout << "\nSitemized publish..." << endl;
      mqtt::delivery_token_ptr publish_token;
      publish_token = client.publish(topic, message2.c_str(), message2.size(), /*QOS*/1, false);
      cout << "token:[" << publish_token->get_message_id() << "]\n";
      cout << "message len:[" << publish_token->get_message()->get_payload().size() << "]"<< " bytes\n";
      publish_token->wait_for(time_out);
      cout << "done.\n" << endl;
    };

    /* Now try with a listener,该方法绑定发送的回调函数 */ {
      cout << "Custom callback function(with token)...\n" << endl;
      action_listener listener;// 回调函数类
      mqtt::message_ptr publish_msg = mqtt::make_message(topic, message1.c_str());// 消息组装
      mqtt::delivery_token_ptr publish_token = client.publish(publish_msg, nullptr, listener);// 发送消息并绑定回调函数
      publish_token->wait();
      cout << "done.\n" << endl;
    };

    /* Finally try with a listener, but no token. */ {
      cout << "Custom callback function(without token)...\n" << endl;
      delivery_action_listener deliveryListener;
      mqtt::message_ptr publish_msg = mqtt::make_message(topic, message4);
      client.publish(publish_msg, nullptr, deliveryListener);

      while (!deliveryListener.is_done()) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
      cout << "done.\n" << endl;
    };

    /* Double check that there are no pending tokens */ {
      auto toks = client.get_pending_delivery_tokens();
      if (!toks.empty())
        cout << "Error: There are pending delivery tokens!" << endl;
      else
        cout <<"===\n";
    }

    /* Disconnect. */ {
      cout << "Disconnecting...\n" << endl;
      client.disconnect()->wait();
      cout << "done.\n" << endl;
    }
  }
  catch (const mqtt::exception& exc) {
    std::cerr <<exc.what() << endl;
    return ;
  }

};

};// namespace method_11_cpp_pub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_11_CPP_PUB_H_
