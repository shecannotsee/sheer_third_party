//
// Created by shecannotsee on 2023/2/14.
//

#ifndef MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_7_ASYNC_SSL_PUB_H_
#define MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_7_ASYNC_SSL_PUB_H_

#include <string.h>
#include <iostream>
#include <string>
#include <MQTTAsync.h>

namespace method_7_async_ssl_pub {

void processing_results (int return_code, const std::string& method_name) {
  if ( return_code != MQTTASYNC_SUCCESS ) {
    std::cout<<"Failed to["<<method_name<<"],return code"<<return_code<<std::endl;
    exit(EXIT_FAILURE);
  } else {
    //cout<<method_name<<" success"<<endl;
  }
};

void main() {
  std::string server_url = "tcp://localhost:1883";
  std::string client_id  = "method_7_client";

  MQTTAsync client;/* init & create*/ {
    MQTTAsync_createOptions create_options = MQTTAsync_createOptions_initializer;/* init */ {
      create_options.sendWhileDisconnected = 1;
    };
    processing_results(
        MQTTAsync_createWithOptions(&client,server_url.c_str(),client_id.c_str(),MQTTCLIENT_PERSISTENCE_NONE,NULL,&create_options),
        "MQTTAsync_createWithOptions"
        );
  };
  /* set callbacks */ {
    processing_results(MQTTAsync_setCallbacks(client, client, NULL, /*messageArrived*/NULL, NULL),"");
  };
  /* connect */ {
    MQTTAsync_connectOptions conn_opts  = MQTTAsync_connectOptions_initializer;
    MQTTAsync_SSLOptions ssl_opts       = MQTTAsync_SSLOptions_initializer;
    MQTTAsync_willOptions will_opts     = MQTTAsync_willOptions_initializer;
    // 若使用mqttv5的示例
    if (std::stoi("MQTTVERSION_5")==MQTTVERSION_5) {
      MQTTAsync_connectOptions conn_opts5 = MQTTAsync_connectOptions_initializer5;
      conn_opts                           = conn_opts5;
      conn_opts.onSuccess5                = NULL;// onConnect5;
      conn_opts.onFailure5                = NULL;// onConnectFailure5;
      conn_opts.cleanstart                = 1;
    } else {
      conn_opts.onSuccess    = NULL;// onConnect;
      conn_opts.onFailure    = NULL;// onConnectFailure;
      conn_opts.cleansession = 1;
    };
    conn_opts.keepAliveInterval  = 1;// opts.keepalive;
    conn_opts.username           = "opts.username";
    conn_opts.password           = "opts.password";
    conn_opts.MQTTVersion        = MQTTVERSION_3_1;"opts.MQTTVersion";
    conn_opts.context            = client;
    conn_opts.automaticReconnect = 1;
    conn_opts.httpProxy          = "opts.http_proxy";
    conn_opts.httpsProxy         = "opts.https_proxy";

    if ("opts.will_topic") /* will options */ {
      will_opts.message   = "opts.will_payload";
      will_opts.topicName = "opts.will_topic";
      will_opts.qos       = 1;// opts.will_qos;
      will_opts.retained  = 1;// opts.will_retain;
      conn_opts.will      = &will_opts;
    };

    if (opts.connection && (strncmp(opts.connection, "ssl://", 6) == 0 || strncmp(opts.connection, "wss://", 6) == 0)) {
      if (opts.insecure)
        ssl_opts.verify = 0;
      else
        ssl_opts.verify = 1;
      ssl_opts.CApath              = opts.capath;
      ssl_opts.keyStore            = opts.cert;
      ssl_opts.trustStore          = opts.cafile;
      ssl_opts.privateKey          = opts.key;
      ssl_opts.privateKeyPassword  = opts.keypass;
      ssl_opts.enabledCipherSuites = opts.ciphers;
      ssl_opts.ssl_error_cb        = onSSLError;
      ssl_opts.ssl_error_context   = client;
      ssl_opts.ssl_psk_cb          = onPSKAuth;
      ssl_opts.ssl_psk_context     = &opts;
      conn_opts.ssl                = &ssl_opts;
    }

    processing_results(MQTTAsync_connect(client, &conn_opts),"MQTTAsync_connect");

  };

  char message[] = "hello world";
  int len = (int)strlen(message);
  /* publish */ {
    /* 为了内存安全,需要在此处校验消息的长度? */
    MQTTAsync_responseOptions pub_opts = MQTTAsync_responseOptions_initializer;
    pub_opts.onSuccess = NULL;
    pub_opts.onFailure = NULL;
    processing_results(MQTTAsync_send(client, "topic", len, message, 1, 1, &pub_opts),"MQTTAsync_send");
  };

  /* disconnect */ {
    MQTTAsync_disconnectOptions disc_opts = MQTTAsync_disconnectOptions_initializer;/* set */ {
      disc_opts.onSuccess = NULL;
    };
    processing_results(MQTTAsync_disconnect(client, &disc_opts),"MQTTAsync_disconnect");
  };

  /* destroy */ {
    MQTTAsync_destroy(&client);
  };

};

};// namespace method_7_async_ssl_pub



#endif //MQTT_LIB_TEST_MQTT_LIB_TEST_METHOD_7_ASYNC_SSL_PUB_H_
