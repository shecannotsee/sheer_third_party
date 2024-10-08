//
// Created by shecannotsee on 2022/12/27.
//

#ifndef OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_2_H_
#define OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_2_H_

#include <string.h>

#include <iostream>
#include <string>

#include <openssl/aes.h>
#include <openssl/evp.h>

// 一个去掉注释的加密解密流程,与method_1完全一样
namespace method_2 {

void print_error(std::string function_name, int ret) {
  if (ret==1) {
    // success to execution
  } else if (ret == 0) {
    std::cout<<function_name<<" execution failed.\n";
  } else {
    std::cout<<function_name<<" unknown error.\n";
  }
}

void main() {
  const unsigned char data[] = "shecannotsee"; // len = 12字节
  const unsigned char iv[]   = "1234567890123456";// 初始向量,16字节,128位
  const unsigned char key[]  = "shecannotseeZZZZ";// 密钥,16字节,128位

  unsigned char mid_data[]   = "shecannotsee3456";// 中间变量的长度应该为16字节(128位)的n倍
  /* 加密 */ {
    std::cout<<"\n明文变为密文"<<std::endl;
    int ret = -1;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    ret = EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(),NULL, key, iv, /*加密*/AES_ENCRYPT);/* info */ {
      print_error("EVP_CipherInit_ex", ret);
    };
    int temp = -1;
    ret = EVP_CipherUpdate(ctx, mid_data, &temp, data, 12);/* info */ {
      print_error("EVP_CipherUpdate", ret);
      std::cout << "\"shecannotsee\"输出的数据长度为[" << temp << "]" << std::endl;
    }
    ret = EVP_CipherFinal(ctx, mid_data, &temp);/* info */ {
      print_error("EVP_CipherFinal", ret);
      std::cout << "\"shecannotsee\"输出的数据长度为[" << temp << "]" << std::endl;
    }
    EVP_CIPHER_CTX_free(ctx);
    std::cout<<"mid_data["<<mid_data<<"]"<<strlen((char*)mid_data)<<std::endl;
  };

  /* 解密 */ {
    std::cout<<"\n密文还原为明文"<<std::endl;
    int ret = -1;
    unsigned char DE_buffer[] = "1234567890123456";// 长度需要为16字节的倍数
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit_ex(ctx,EVP_aes_128_cbc(),NULL,key,iv,/*解密*/AES_DECRYPT);/* info */ {
      print_error("EVP_CipherInit_ex", ret);
    }
    int temp = -1;
    ret = EVP_CipherUpdate(ctx, DE_buffer, &temp, mid_data, 16);/* info */ {
      print_error("EVP_CipherUpdate", ret);
      std::cout << "after EVP_CipherUpdate,\"shecannotsee\"输出的数据长度为[" << temp << "]" << std::endl;
    }
    ret = EVP_CipherFinal(ctx, DE_buffer, &temp); /* info */ {
      print_error("EVP_CipherFinal", ret);
      std::cout << "after EVP_CipherFinal,\"shecannotsee\"输出的数据长度为[" << temp << "]" << std::endl;
    }
    EVP_CIPHER_CTX_free(ctx);

    // 实际从密文翻译成原始明文后的长度不一定是16字节的倍数，所以需要从16字节倍数的缓冲区中取得一定长度的有效原始明文
    unsigned char* p = new unsigned char[temp];
    memcpy(p,DE_buffer,temp);

    std::cout<<"原始明文为["<<p<<"]"<<std::endl;
    delete []p;
    p = nullptr;
  };

};

};// namespace method_2

#endif //OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_2_H_
