//
// Created by shecannotsee on 2023/2/7.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_2_SUB_ASYNC_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_2_SUB_ASYNC_H_

#include <iostream>
#include <string>
#include <MQTTClient.h>

namespace method_2_sub {
using ::std::string;
using ::std::cout;
using ::std::endl;
// 使用方法1中的结果处理函数
using ::method_1_publish_sync::processing_results;
using ::method_1_publish_sync::Message_pass_at_least_once;

volatile MQTTClient_deliveryToken deliveredtoken;

void delivered(void *context, MQTTClient_deliveryToken dt) {
  printf("Message with token value [%d] delivery confirmed\n", dt);
  deliveredtoken = dt;
}

int msgarrvd(void *context, char *topicName, int topicLen, MQTTClient_message *message) {
  printf("Message arrived\n");
  printf("     topic: [%s]\n", topicName);
  printf("   message: [%.*s]\n", message->payloadlen, (char*)message->payload);
  MQTTClient_freeMessage(&message);
  MQTTClient_free(topicName);
  return 1;
}

void connlost(void *context, char *cause) {
  printf("\nConnection lost\n");
  printf("     cause: %s\n", cause);
}


void main() {
//////////////////////////////////////mqtt异步订阅///////////////////////////////////////////////////////////////////////
  string server_url = "tcp://localhost:1883";
  string topic_name = "MQTT Examples";
  string client_id = "client_to_need_data";

  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;/* init */{
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
  };
  int return_code = 0;

  return_code = MQTTClient_create(&client, server_url.c_str(), client_id.c_str(), MQTTCLIENT_PERSISTENCE_NONE, NULL); {
    processing_results(return_code, "MQTTClient_create");
  }
  return_code = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered); {
    processing_results(return_code, "MQTTClient_setCallbacks");
  };
  return_code = MQTTClient_connect(client, &conn_opts); {
    processing_results(return_code, "MQTTClient_connect");
  };
  /* log */ {
    cout<<"Subscribing to topic ["<<topic_name<<"]"<<endl;
    cout<<"for client ["<<client_id<<"] using QoS["<<Message_pass_at_least_once<<"]"<<endl;
  };
  return_code = MQTTClient_subscribe(client, topic_name.c_str(), Message_pass_at_least_once); {
    processing_results(return_code, "MQTTClient_subscribe");
  };
  /* quit */ {
    cout<< "Press Q<Enter> to quit\n\n";
    int ch;
    do {
      ch = getchar();
    } while (ch!='Q' && ch != 'q');
  }
  return_code = MQTTClient_unsubscribe(client, topic_name.c_str()); {
    processing_results(return_code, "MQTTClient_unsubscribe");
  };
  return_code = MQTTClient_disconnect(client, 10000); {
    processing_results(return_code, "MQTTClient_disconnect");
  };

  MQTTClient_destroy(&client);
};

};// namespace method_2_sub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_2_SUB_ASYNC_H_
