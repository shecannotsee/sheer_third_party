//
// Created by shecannotsee on 2023/2/9.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_5_ASYNC_SUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_5_ASYNC_SUB_H_

#include <iostream>
#include <string>
#include <atomic>
#include <MQTTAsync.h>

namespace method_5_async_sub {
using ::std::string;
using ::std::cout;
using ::std::endl;

// 1:任务已经完成 0:任务未完成
std::atomic<int> finished {0};
// 1:用户已经订阅 0:用户未订阅
std::atomic<int> subscribed{0};
// 1:活动弄已经结束 0:活动未结束
std::atomic<int> disc_finished{0};

std::atomic<bool> some_errors_have_occurred{false};

void main() {
///////////////////////////////////mqtt异步订阅//////////////////////////////////////////////////////////////////////////
  static string server_url = "tcp://localhost:1883";
  static string client_id = "async_subscriber_client";
  static string topic_name = "MQTT_example";
  // 返回值处理函数
  static auto processing_results = [](int return_code, const string& method_name) {
    if ( return_code != MQTTASYNC_SUCCESS ) {
      cout<<"Failed to["<<method_name<<"],return code"<<return_code<<endl;
      exit(EXIT_FAILURE);
    } else {
      //cout<<method_name<<" success"<<endl;
    }
  };

  MQTTAsync client;/* init & create */ {
    processing_results(MQTTAsync_create(&client, server_url.c_str(), client_id.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL),
                       "MQTTAsync_create");
  };

  /* 对client设置操作相应的回调函数 */ {
    // 连接失败处理函数,该函数更多出现在客户端和服务器连上后,然后心跳消失时调用
    auto connlost = [](void *context, char *cause) -> void {
      /* log */ {
        cout << "\nConnection lost\n";
        cout << "cause: " << cause << "\n";
        cout << "Reconnecting\n";
      };
      MQTTAsync client = (MQTTAsync)context;
      MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;/* set */ {
        conn_opts.onSuccess = [](void* context, MQTTAsync_successData* response){};
        conn_opts.onFailure = [](void* context, MQTTAsync_failureData* response){
          some_errors_have_occurred = true;
        };
        conn_opts.keepAliveInterval = 20;
        conn_opts.cleansession = 1;
      };
      // 重新连接一次
      processing_results(MQTTAsync_connect(client, &conn_opts), "MQTTAsync_connect");
    };
    // 收到消息处理函数
    auto msgarrvd = [](void *context, char *topicName, int topicLen, MQTTAsync_message *message) -> int {
      printf("Message arrived\n");
      printf("     topic: %s\n", topicName);
      printf("   message: %.*s\n", message->payloadlen, (char*)message->payload);
      MQTTAsync_freeMessage(&message);
      MQTTAsync_free(topicName);
      return 1;
    };

    processing_results(MQTTAsync_setCallbacks(client, client, connlost, msgarrvd, NULL),
                       "MQTTAsync_setCallbacks");
  };

  /* 连接选项设置 */
  MQTTAsync_connectOptions conn_opts = MQTTAsync_connectOptions_initializer;/* set */ {
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;

    // 连接到服务器成功的回调函数
    auto onConnect = [](void* context, MQTTAsync_successData* response) {
      cout << "Successful connection\n";
      cout << "Subscribing to topic [" << topic_name << "]\n";
      cout << "for client [" << client_id << "] using QoS["<<1<<"]\n\n";
      MQTTAsync client = (MQTTAsync)context;
      // 订阅动作的回调函数设置
      MQTTAsync_responseOptions opts = MQTTAsync_responseOptions_initializer;/* set */ {
        // 订阅主题成功对应的回调函数
        opts.onSuccess = [](void* context, MQTTAsync_successData* response) -> void {
          cout << "Subscribe succeeded\n";
        };;

        // 订阅主题失败对应的回调函数
        opts.onFailure = [](void* context, MQTTAsync_failureData* response) ->void {
          cout<<"Subscribe failed, rc ["<< response->code <<"]\n";
          some_errors_have_occurred = true;
        };;

        opts.context = client;
      };
      // 订阅动作
      processing_results(MQTTAsync_subscribe(client, topic_name.c_str(), 1, &opts),"MQTTAsync_subscribe");
    };
    conn_opts.onSuccess = onConnect;

    // 连接服务器失败的回调函数
    auto onConnectFailure = [](void* context, MQTTAsync_failureData* response) {
      cout << "Connect failed, rc ["<< response->code <<"]\n";
      some_errors_have_occurred = true;
    };
    conn_opts.onFailure = onConnectFailure;

    conn_opts.context = client;
  };

  /* 连接mqtt服务器 */
  processing_results(MQTTAsync_connect(client, &conn_opts), "MQTTAsync_connect");

  /* quit */ {
    for (int ch = 0;ch != 'q'&& ch != 'Q';) {
      if (some_errors_have_occurred) {
        cout << "some_errors_have_occurred";
        ch = 'q';
      } else {
        ch = getchar();
      }
    }
  };

  /* 断开连接 */
  MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;/* set */ {
      auto onDisconnect = [](void* context, MQTTAsync_successData* response) ->void {
        cout << "Successful disconnection\n";
        printf("Successful disconnection\n");
        some_errors_have_occurred = false;
      };
      disc_opts.onSuccess = onDisconnect;

      auto onDisconnectFailure = [](void* context, MQTTAsync_failureData* response) ->void {
        cout << "Disconnect failed, rc [" << response->code << "]\n";
        some_errors_have_occurred = true;
      };
      disc_opts.onFailure = onDisconnectFailure;
    };
  processing_results(MQTTAsync_disconnect(client, &disc_opts), "MQTTAsync_disconnect");

  if (some_errors_have_occurred) {
    cout << "MQTTAsync_disconnect failed.\n";
  }

  MQTTAsync_destroy(&client);
};


};// namespace method_5_async_sub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_5_ASYNC_SUB_H_
