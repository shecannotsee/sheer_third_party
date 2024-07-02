//
// Created by shecannotsee on 2023/2/7.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_METHOD_1_PUBLISH_SYNC_H_
#define MQTT_LIB_TEST_MQTT_LIB_METHOD_1_PUBLISH_SYNC_H_

#include <string.h>
#include <iostream>
#include <string>
#include <MQTTClient.h>

namespace method_1_publish_sync {
using ::std::cout;
using ::std::endl;
using ::std::string;

enum : int {
  Message_pass_at_least_once = 1
};

void processing_results(int return_code, const string& method_name) {
  if ( return_code != MQTTCLIENT_SUCCESS ) {
    cout<<"Failed to["<<method_name<<"],return code"<<return_code<<endl;
    exit(EXIT_FAILURE);
  }
  else {
//    cout<<method_name<<" success"<<endl;
  }
};

void main() {
//////////////////////////////////////////mqtt同步发布///////////////////////////////////////////////////////////////////
  string server_url = "tcp://localhost:1883";
  char msg[] = "Hello World!----from push sync";
  string topic_name = "MQTT Examples";
  string client_id = "client_to_push_data_sync";

  MQTTClient client;
  MQTTClient_connectOptions conn_opts = MQTTClient_connectOptions_initializer; {
    conn_opts.keepAliveInterval = 20;
    conn_opts.cleansession = 1;
  };
  MQTTClient_message pubmsg = MQTTClient_message_initializer;/* init */ {
    pubmsg.payload = static_cast<void*>(msg);
    pubmsg.payloadlen = static_cast<int>((int)strlen(msg));
    pubmsg.qos = Message_pass_at_least_once;// please the notes
    pubmsg.retained = false;// please the notes
  };
  MQTTClient_deliveryToken token;

  int return_code = 0;
  return_code = MQTTClient_create(&client,server_url.c_str(),client_id.c_str(), MQTTCLIENT_PERSISTENCE_NONE,NULL); {
    processing_results(return_code,"MQTTClient_create");
  };
  return_code = MQTTClient_connect(client, &conn_opts); {
    processing_results(return_code,"MQTTClient_connect");
  };
  return_code = MQTTClient_publishMessage(client, topic_name.c_str(), &pubmsg, &token); {
    processing_results(return_code,"MQTTClient_publishMessage");
  };

  long timeout = 10000;
  /* log */ {
    cout << "Waiting for up to [" << (timeout / 1000) << "] seconds for publication of [" << msg << "]\n";
    cout << "on topic [" << topic_name << "] for client with ClientID: [" << client_id << "]\n";
  }

  return_code = MQTTClient_waitForCompletion(client, token, timeout); {
    processing_results(return_code, "MQTTClient_waitForCompletion");
  }
  /* log */ {
    cout<<"Message with delivery token ["<<token<<"] delivered\n";
  }

  return_code = MQTTClient_disconnect(client, static_cast<int>(timeout)); {
    processing_results(return_code, "MQTTClient_disconnect");
  }

  MQTTClient_destroy(&client);
};

};// namespace method_1_publish_sync

#endif //MQTT_LIB_TEST_MQTT_LIB_METHOD_1_PUBLISH_SYNC_H_
