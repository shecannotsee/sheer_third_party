//
// Created by shecannotsee on 2022/12/29.
//

#ifndef OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_AES_CBC_128_INTERFACE_H_
#define OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_AES_CBC_128_INTERFACE_H_

#include <string.h>

#include <iostream>
#include <string>
#include <memory>
#include <random>

#include <openssl/aes.h>
#include <openssl/evp.h>


// aes cbc 128接口代码
namespace aes_cbc_128_interface {

static const int aes_cbc_128_bytes = 16;// 16bytes = 128 bits

std::unique_ptr<unsigned char[]> string_to_uchar(std::string str) {
  std::unique_ptr<unsigned char[]> ret = std::make_unique<unsigned char[]>(str.size());
  for (int i=0; i<str.size(); i++) {
    ret[i] = static_cast<unsigned char>(str[i]);
  }
  return ret;
}
std::string uchar_to_string(unsigned char* uchar, int len) {
  std::string ret;
  for (int i=0; i<len; i++) {
    ret += static_cast<char>(uchar[i]);
  }
  return ret;
}

void print_error(std::string function_name, int ret) {
  if (ret==1) {
    // success to execution
  } else if (ret == 0) {
    std::cout<<function_name<<" execution failed.\n";
  } else {
    std::cout<<function_name<<" unknown error.\n";
  }
}

namespace PlaintextToCiphertext/*加密*/ {
  std::string method(std::string plaintext, std::string cipher, std::string iv) {
    /* data verification */ {
      if (cipher.size() == aes_cbc_128_bytes && iv.size() == aes_cbc_128_bytes) {
        std::cout<<"data verification pass.\n";
      } else {
        return "[error]cipher or iv is not 128 bits.\n";
      }
    };

    /* data preprocessing */
    // 用来判断函数是否成功运行
    int ret = -1;
    // 计算buffer的长度,长度应为
    unsigned long ciphertext_len = ((plaintext.size()-1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    // 生成buffer,用来存储密文
    std::unique_ptr<unsigned char[]> ciphertext = std::make_unique<unsigned char[]>(ciphertext_len);
    // 用于传递加密前后的长度变量
    int after_len = -1;

    /* main deal */ {
      EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
      ret = EVP_CipherInit_ex(ctx,EVP_aes_128_cbc(),NULL,
                              /*key*/string_to_uchar(cipher).get(),
                              /*iv*/string_to_uchar(iv).get(),
                              /*加密*/AES_ENCRYPT);/*info*/ {
        print_error("EVP_CipherInit_ex",ret);
      };
      ret = EVP_CipherUpdate(ctx,
                             /*out*/ciphertext.get(),
                             /*out_len*/&after_len,
                             /*in unsigned char array*/string_to_uchar(plaintext).get(),
                             /*deal bytes*/plaintext.size());/*info*/ {
        print_error("EVP_CipherUpdate",ret);
      };
      ret = EVP_CipherFinal(ctx, ciphertext.get(), &after_len); /* info */ {
        print_error("EVP_CipherFinal",ret);
      }
      EVP_CIPHER_CTX_free(ctx);
    };

    return uchar_to_string(ciphertext.get(), ciphertext_len);
  }
};

namespace CiphertextToPlaintext/*解密*/ {
  std::string method(std::string ciphertext, std::string cipher, std::string iv) {
    /* data verification */ {
      if (cipher.size() == aes_cbc_128_bytes && iv.size() == aes_cbc_128_bytes) {
        std::cout<<"data verification pass.\n";
      } else {
        return "[error]cipher or iv is not 128 bits.\n";
      }
    };

    /* data preprocessing */
    // 用来判断函数是否成功运行
    int ret = -1;
    // 计算buffer的长度,长度应为
    unsigned long plaintext_len = ( (ciphertext.size()-1) / AES_BLOCK_SIZE + 1) * AES_BLOCK_SIZE;
    // 生成buffer,用来存储明文
    std::unique_ptr<unsigned char[]> plaintext = std::make_unique<unsigned char[]>(plaintext_len);
    // 用于传递加密前后的长度变量
    int after_len = -1;

    /* main deal */ {
      EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
      ret = EVP_CipherInit_ex(ctx, EVP_aes_128_cbc(), NULL,
                              /*key*/string_to_uchar(cipher).get(),
                              /*iv*/string_to_uchar(iv).get(),
                              /*解密*/AES_DECRYPT);/* info */ {
        print_error("EVP_CipherInit_ex",ret);
      };
      ret = EVP_CipherUpdate(ctx,
                             plaintext.get(),
                             &after_len,
                             string_to_uchar(ciphertext).get(),
                             plaintext_len);/* info */ {
        print_error("EVP_CipherUpdate",ret);

      };
      ret = EVP_CipherFinal(ctx, plaintext.get(), &after_len); /* info */ {
        print_error("EVP_CipherFinal",ret);
      };
      EVP_CIPHER_CTX_free(ctx);
    };

    return uchar_to_string(plaintext.get(),after_len);
  }
};

void main() {
  std::cout<<"interface test"<<std::endl;
  std::string plaintext = "shecannotsee";// 明文
  std::string cipher    = "1234567890123456";// 密钥
  std::string iv        = "shecannotseeZZZZ";// 初始向量

  std::cout<<"";
  std::string ciphertext = PlaintextToCiphertext::method(plaintext, cipher, iv);
  std::cout<<ciphertext.size()<<"["<<ciphertext<<"]"<<std::endl;

  std::string original_plaintext = CiphertextToPlaintext::method(ciphertext, cipher, iv);
  std::cout<<original_plaintext.size()<<"["<<original_plaintext<<"]"<<std::endl;

  /* test */ {
    std::random_device rd;
    int error_num = 0;
    int success_num = 0;
    for (int i=0; i<10000; i++) {
      std::string temp = std::to_string((int)rd());
      if (temp != CiphertextToPlaintext::method(PlaintextToCiphertext::method(temp,cipher,iv),cipher,iv)) {
        std::cout<<"error"<<++error_num<<std::endl;
        exit(1);
      } else {
        std::cout<<"success"<<++success_num<<std::endl;
      }
    }


  }

};

};// namespace aes_cbc_128_interface

#endif //OPENSSL_3_0_0_TEST_OPENSSL3_0_0_INTERFACE_TEST_AES_CBC_128_INTERFACE_H_
