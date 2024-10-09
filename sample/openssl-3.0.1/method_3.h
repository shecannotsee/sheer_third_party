//
// Created by shecannotsee on 2022/12/28.
//

#ifndef OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_3_H_
#define OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_3_H_

#include <openssl/evp.h>

// 该方法无法正常运行
namespace method_3 {

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
  // 明文buffer
  unsigned char plaintext[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  int plaintext_len = strlen((char*)plaintext);
  // 密文buffer
  unsigned char* ciphertext = nullptr;
  int ciphertext_len ;/* buffer 长度处理 */ {
    ciphertext_len = (plaintext_len/AES_BLOCK_SIZE+1)*AES_BLOCK_SIZE;
    std::cout<<"明文字节长度["<<plaintext_len<<"]"<<std::endl;
    std::cout<<"密文长度["<<ciphertext_len<<"]"<<std::endl;
    ciphertext = new unsigned char[ciphertext_len];
  };

  // 密钥
  unsigned char key[] = "1234567890123456";
  // 初始向量 (IV)
  unsigned char iv[]  = "1234567890123456";

  /* 加密 */ {
    std::cout<<"\n加密"<<std::endl;
    int ret = -1;
    // 初始化加密上下文
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    // 设置加密模式为 AES-CBC 128
    ret = EVP_CipherInit_ex(ctx, /*加密算法*/EVP_aes_128_cbc(), NULL, key, iv, /*加密*/AES_ENCRYPT);/* info print */ {
      print_error("EVP_CipherInit_ex", ret);
    }
    AES_BLOCK_SIZE;// 16字节
    // 输出缓冲区
    unsigned char out[1024];
    int outl;
    // 加密第一块数据
    ret = EVP_CipherUpdate(ctx, out, &outl, plaintext, 10);/* info printf */ {
      print_error("EVP_EncryptUpdate", ret);
      std::cout << "加密第一块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    }
    // 加密第二块数据
    ret = EVP_CipherUpdate(ctx, out, &outl, plaintext + 10, 10);/* info printf */ {
      print_error("EVP_EncryptUpdate", ret);
      std::cout << "加密第二块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    }
    // 加密第三块数据
    ret = EVP_CipherUpdate(ctx, out, &outl, plaintext + 20, 6);/* info printf */ {
      print_error("EVP_EncryptUpdate", ret);
      std::cout << "加密第三块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    }
    // 完成加密过程
    ret = EVP_CipherFinal(ctx, out, &outl);/* info printf */ {
      print_error("EVP_CipherFinal", ret);
      std::cout << "完成加密过程after EVP_EncryptFinal[" << outl << "]" << std::endl;
    }
    // 释放加密上下文
    EVP_CIPHER_CTX_free(ctx);
    memcpy(ciphertext,out,ciphertext_len);
    std::cout<<"密文(ciphertext)为["<<ciphertext<<"]"<<std::endl;
  };


  /* 解密 */ {
    std::cout<<"\n解密"<<std::endl;
    // 初始化加密上下文
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    // 设置加密模式为 AES-CBC 128
    EVP_CipherInit_ex(ctx, /*加密算法*/EVP_aes_128_cbc(), NULL, key, iv, /*解密*/AES_DECRYPT);
    AES_BLOCK_SIZE;// 16字节
    // 输出缓冲区
    unsigned char out[1024];
    int outl;

    // 加密第一块数据
    EVP_CipherUpdate(ctx, out, &outl, ciphertext, 10);

    std::cout << "加密第一块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    // 加密第二块数据
    EVP_CipherUpdate(ctx, out, &outl, ciphertext + 10, 10);
    std::cout << "加密第二块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    // 加密第三块数据
    EVP_CipherUpdate(ctx, out, &outl, ciphertext + 20, 6);
    std::cout << "加密第三块数据after EVP_EncryptUpdate[" << outl << "]" << std::endl;
    // 完成加密过程
    EVP_CipherFinal(ctx, out, &outl);
    std::cout << "after EVP_EncryptFinal[" << outl << "]" << std::endl;
    // 释放加密上下文
    EVP_CIPHER_CTX_free(ctx);


    unsigned char* p = new unsigned char[26];
    memcpy(p,out,26);

    std::cout<<"原始明文为["<<p<<"]"<<std::endl;
    delete []p;
    p = nullptr;
  };


};

};// namespace method_3

#endif //OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_METHOD_3_H_
