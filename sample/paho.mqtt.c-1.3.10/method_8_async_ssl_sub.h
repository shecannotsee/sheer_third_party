//
// Created by shecannotsee on 2023/2/14.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_8_ASYNC_SSL_SUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_8_ASYNC_SSL_SUB_H_

#include <string>
#include <MQTTAsync.h>

namespace method_8_async_ssl_sub {

void main() {
  static std::string server_url = "tcp://localhost:1883";
  static std::string client_id  = "method_8_client";
  static std::string topic_name = "hello world";

  MQTTAsync client;
  MQTTAsync_createOptions create_options = MQTTAsync_createOptions_initializer;/* set */ {};
  MQTTAsync_createWithOptions(&client,server_url.c_str(),client_id.c_str(),MQTTCLIENT_PERSISTENCE_NONE,NULL,&create_options);
  MQTTAsync_setCallbacks(client, client, NULL, NULL/*messageArrived*/, NULL);

  MQTTAsync_SSLOptions ssl_options = MQTTAsync_SSLOptions_initializer;
  /* ssl set*/
  if (opts.connection && (strncmp(opts.connection, "ssl://", 6) == 0 || strncmp(opts.connection, "wss://", 6) == 0)) {
    ssl_options.verify              = (opts.insecure) ? 0 : 1;
    ssl_options.CApath              = opts.capath;
    ssl_options.keyStore            = opts.cert;
    ssl_options.trustStore          = opts.cafile;
    ssl_options.privateKey          = opts.key;
    ssl_options.privateKeyPassword  = opts.keypass;
    ssl_options.enabledCipherSuites = opts.ciphers;
    conn_opts.ssl                = &ssl_opts;
  }

  MQTTAsync_connectOptions connect_options = MQTTAsync_connectOptions_initializer;/* set */ {
    auto onConnect = [](void* context, MQTTAsync_successData* response){
      MQTTAsync client                = (MQTTAsync)context;
      MQTTAsync_responseOptions response_options = MQTTAsync_responseOptions_initializer;/* set */ {
        response_options.onSuccess = NULL;//onSubscribe;
        response_options.onFailure = NULL;//onSubscribeFailure;
        response_options.context   = client;
      };
      MQTTAsync_subscribe(client, topic_name.c_str(), /*opts.qos*/1, &response_options);
    };
    connect_options.onSuccess    = onConnect;//onConnect;
    connect_options.onFailure    = NULL;//onConnectFailure;
    connect_options.cleansession = 1;

    connect_options.keepAliveInterval  = 20;// opts.keepalive;
    connect_options.username           = "opts.username";
    connect_options.password           = "opts.password";
    connect_options.MQTTVersion        = MQTTVERSION_DEFAULT;//opts.MQTTVersion;
    connect_options.context            = client;
    connect_options.automaticReconnect = 1;
    connect_options.httpProxy          = "opts.http_proxy";
    connect_options.httpsProxy         = "opts.https_proxy";
  };
  MQTTAsync_connect(client, &connect_options);

  MQTTAsync_disconnectOptions disconnect_options = MQTTAsync_disconnectOptions_initializer;/* set */ {
    disconnect_options.onSuccess = NULL;
    disconnect_options.onFailure = NULL;
  };
  MQTTAsync_disconnect(client,&disconnect_options);

  MQTTAsync_destroy(&client);
};

};// namespace method_8_async_ssl_sub

#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_8_ASYNC_SSL_SUB_H_
