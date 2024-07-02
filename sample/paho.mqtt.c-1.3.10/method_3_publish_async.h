//
// Created by shecannotsee on 2023/2/7.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_3_PUBLISH_ASYNC_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_3_PUBLISH_ASYNC_H_

#include <iostream>
#include <string>
#include <MQTTClient.h>
#include <unistd.h>

namespace method_3_publish_async {
using ::std::string;
using ::std::cout;
using ::std::endl;
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
///////////////////////////////////////mqtt异步发布//////////////////////////////////////////////////////////////////////
  string server_url = "tcp://localhost:1883";
  char msg[] = "Hello World!----from push async";
  string topic_name = "MQTT Examples";
  string client_id = "client_to_push_data_async";

  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer;/* init */ {
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
  };
  MQTTClient_message pubmsg = MQTTClient_message_initializer;/* init */ {
    pubmsg.payload = msg;
    pubmsg.payloadlen = (int)strlen(msg);
    pubmsg.qos = Message_pass_at_least_once;
    pubmsg.retained = 0;
    deliveredtoken = 0;
  };
  MQTTClient_deliveryToken token;

  int return_code =0 ;
  return_code = MQTTClient_create(&client, server_url.c_str(), client_id.c_str(),MQTTCLIENT_PERSISTENCE_NONE, NULL); {
    processing_results(return_code, "MQTTClient_create");
  };
  return_code = MQTTClient_setCallbacks(client, NULL, connlost, msgarrvd, delivered); {
    processing_results(return_code, "MQTTClient_setCallbacks");
  };
  return_code = MQTTClient_connect(client, &conn_opts); {
    processing_results(return_code, "MQTTClient_connect");
  };
  return_code = MQTTClient_publishMessage(client, topic_name.c_str(), &pubmsg, &token); {
    processing_results(return_code, "MQTTClient_publishMessage");
  };

  /* log */ {
    cout<<"Waiting for publication of ["<<Message_pass_at_least_once<<"]\n";
    cout<<"on topic ["<<topic_name<<"] for client with ClientID: ["<<client_id<<"]\n";
  };
  while (deliveredtoken != token) {
    sleep(10);
    return_code = MQTTClient_publishMessage(client, topic_name.c_str(), &pubmsg, &token); {
      processing_results(return_code, "MQTTClient_publishMessage");
    };
  };

  MQTTClient_destroy(&client);

};

};// namespace method_3_publish_async

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_3_PUBLISH_ASYNC_H_
