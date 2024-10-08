//
// Created by shecannotsee on 2022/12/27.
//

#ifndef OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_1_H_
#define OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_1_H_

#include <string.h>

#include <iostream>
#include <string>

#include <openssl/aes.h>
#include <openssl/evp.h>

// 一个详细的加密解密流程
namespace method_1 {

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
  const unsigned char iv[]   = "1234567890123456";// 16字节,128位
  const unsigned char key[]  = "shecannotseeZZZZ";// 密码,16字节,128位

  unsigned char mid_data[]   = "shecannotsee3456";// 中间变量的长度应该为16字节(128位)的n倍
  /* 加密 */ {
    std::cout<<"\n明文变为密文"<<std::endl;
    int ret = -1;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    ret = EVP_CipherInit_ex(ctx, // 指向密码上下文的指针，在调用该函数时必须已经分配了内存空间
                            EVP_aes_128_cbc(), // 指向加解密算法的指针，用于指定要使用的算法
                            NULL, // 可以添加自己实现的加密解密算法
                            key, // 指向密钥的指针，用于指定加解密使用的密钥。
                            iv, // 指向初始化向量的指针，用于指定加解密使用的初始化向量
                            AES_ENCRYPT // 布尔类型的变量，用于指定当前的操作是加密还是解密。如果为真，则表示执行加密操作；如果为假，则表示执行解密操作
    );
    print_error("EVP_CipherInit_ex",ret);

    int temp = -1;
    ret = EVP_CipherUpdate(ctx, // 指向密码上下文的指针，在调用该函数时必须已经分配了内存空间
                           mid_data, // 指向加解密后的数据的缓冲区的指针，该函数会将加解密后的数据存储到这个缓冲区中
                           &temp, // 指向一个整型变量的指针，用于存储加解密后的数据的长度
                           data, // 指向要加解密的数据的缓冲区的指针，该函数会从这个缓冲区中读取要加解密的数据
                           12 // 要加解密的数据的长度，以字节为单位
    );
    print_error("EVP_CipherUpdate",ret);

    std::cout<<"\"shecannotsee\"输出的数据长度为["<<temp<<"]"<<std::endl;

    ret = EVP_CipherFinal(ctx, // 指向密码上下文的指针，在调用该函数时必须已经初始化了密码上下文
                          mid_data, //指向加解密后的数据的缓冲区的指针，该函数会将加解密后的数据存储到这个缓冲区中
                          &temp // 指向一个整型变量的指针，用于存储加解密后的数据的长度
    );
    print_error("EVP_CipherFinal",ret);

    std::cout<<"\"shecannotsee\"输出的数据长度为["<<temp<<"]"<<std::endl;

    EVP_CIPHER_CTX_free(ctx);
    std::cout<<"mid_data["<<mid_data<<"]"<<strlen((char*)mid_data)<<std::endl;
  };

  /* 解密 */ {
    std::cout<<"\n密文还原为明文"<<std::endl;
    int ret = -1;
    unsigned char DE_buffer[] = "1234567890123456";// 长度需要为16字节的倍数
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_CipherInit_ex(ctx,EVP_aes_128_cbc(),NULL,key,iv,/*解密*/AES_DECRYPT);
    int temp = -1;
    ret = EVP_CipherUpdate(ctx, // 指向密码上下文的指针，在调用该函数时必须已经分配了内存空间
                           DE_buffer, // 指向加解密后的数据的缓冲区的指针，该函数会将加解密后的数据存储到这个缓冲区中
                           &temp, // 指向一个整型变量的指针，用于存储加解密后的数据的长度
                           mid_data, // 指向要加解密的数据的缓冲区的指针，该函数会从这个缓冲区中读取要加解密的数据
                           16 // 要加解密的数据的长度，以字节为单位
    );
    print_error("EVP_CipherUpdate",ret);

    std::cout<<"after EVP_CipherUpdate,\"shecannotsee\"输出的数据长度为["<<temp<<"]"<<std::endl;

    ret = EVP_CipherFinal(ctx, // 指向密码上下文的指针，在调用该函数时必须已经初始化了密码上下文
                          DE_buffer, //指向加解密后的数据的缓冲区的指针，该函数会将加解密后的数据存储到这个缓冲区中
                          &temp // 指向一个整型变量的指针，用于存储加解密后的数据的长度
    );
    print_error("EVP_CipherFinal",ret);

    std::cout<<"after EVP_CipherFinal,\"shecannotsee\"输出的数据长度为["<<temp<<"]"<<std::endl;
    EVP_CIPHER_CTX_free(ctx);

    // 实际从密文翻译成原始明文后的长度不一定是16字节的倍数，所以需要从16字节倍数的缓冲区中取得一定长度的有效原始明文
    unsigned char* p = new unsigned char[temp];
    memcpy(p,DE_buffer,temp);

    std::cout<<"原始明文为["<<p<<"]"<<std::endl;
    delete []p;
    p = nullptr;
  };

};


};// namespace method_1


#endif //OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_1_H_
