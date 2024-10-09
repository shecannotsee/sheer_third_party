//
// Created by  shecannotsee on 2023/1/10.
//

#ifndef OPENSSL_3_0_0_TEST_METHOD_4_RSA_H
#define OPENSSL_3_0_0_TEST_METHOD_4_RSA_H

#include <iostream>
#include <chrono>
#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define LOG(x)               \
        std::cout << x << std::endl;   \


namespace method_4_rsa {
// Source code from
// https://github.com/stevemk14ebr/OpenSSL_Wrapper

const int PUBLIC_KEY_PEM = 1;
const int PRIVATE_KEY_PEM = 0;
const int KEY_LENGTH = 2048;
const int PUBLIC_EXPONENT = 59;// Public exponent should be a prime number.

RSA * create_RSA(RSA * keypair, int pem_type, char *file_name) {

  RSA   *rsa = NULL;
  FILE  *fp  = NULL;

  if(pem_type == PUBLIC_KEY_PEM) {

    fp = fopen(file_name, "w");
    PEM_write_RSAPublicKey(fp, keypair);
    fclose(fp);

    fp = fopen(file_name, "rb");
    PEM_read_RSAPublicKey(fp, &rsa, NULL, NULL);
    fclose(fp);

  }
  else if(pem_type == PRIVATE_KEY_PEM) {

    fp = fopen(file_name, "w");
    PEM_write_RSAPrivateKey(fp, keypair, NULL, NULL, NULL, NULL, NULL);
    fclose(fp);

    fp = fopen(file_name, "rb");
    PEM_read_RSAPrivateKey(fp, &rsa, NULL, NULL);
    fclose(fp);

  }

  return rsa;
}

int public_encrypt(int flen, unsigned char* from, unsigned char* to, RSA* key, int padding) {
  int result = RSA_public_encrypt(flen, from, to, key, padding);
  return result;
}

int private_decrypt(int flen, unsigned char* from, unsigned char* to, RSA* key, int padding) {
  int result = RSA_private_decrypt(flen, from, to, key, padding);
  return result;
}

void create_encrypted_file(char* encrypted, RSA* key_pair) {
  FILE* encrypted_file = fopen("encrypted_file.bin", "w");
  fwrite(encrypted, sizeof(*encrypted), RSA_size(key_pair), encrypted_file);
  fclose(encrypted_file);
}

void main() {
  LOG("OpenSSL_RSA has been started.");

  RSA *private_key;
  RSA *public_key;

  char message[KEY_LENGTH / 8] = "Plain text";
  char *encrypt = NULL;
  char *decrypt = NULL;

  RSA *keypair = NULL;
  BIGNUM *bne = NULL;
  int ret = 0;

  char private_key_pem[12] = "private_key";
  char public_key_pem[11]  = "public_key";

  LOG(KEY_LENGTH);
  LOG(PUBLIC_EXPONENT);

  // RSA *keypair = RSA_generate_key(KEY_LENGTH, PUBLIC_EXPONENT, NULL, NULL); //Old

  bne = BN_new();
  ret = BN_set_word(bne, PUBLIC_EXPONENT);
  if (ret != 1) {
    // goto free_stuff;
    LOG("An error occurred in BN_set_word() method");
  }
  keypair = RSA_new();
  ret = RSA_generate_key_ex(keypair, KEY_LENGTH, bne, NULL);
  if (ret != 1) {
    // goto free_stuff;
    LOG("An error occurred in RSA_generate_key_ex() method");
  }
  LOG("Generate key has been created.");

  private_key = create_RSA(keypair, PRIVATE_KEY_PEM, private_key_pem);
  LOG("Private key pem file has been created.");

  public_key  = create_RSA(keypair, PUBLIC_KEY_PEM, public_key_pem);
  LOG("Public key pem file has been created.");;

  encrypt = (char*)malloc(RSA_size(public_key));
  // 加密开始
  auto start = std::chrono::system_clock::now();
  int encrypt_length = public_encrypt(strlen(message) + 1, (unsigned char*)message, (unsigned char*)encrypt, public_key, RSA_PKCS1_OAEP_PADDING);
  if(encrypt_length == -1) {
    LOG("An error occurred in public_encrypt() method");
  }
  auto end = std::chrono::system_clock::now();
  std::cout<<"加密花费 ["<<
           (std::chrono::time_point_cast<std::chrono::duration<int,std::ratio<1,1000>>>(end)-
            std::chrono::time_point_cast<std::chrono::duration<int,std::ratio<1,1000>>>(start)).count()/* return ms,1s=1000ms*/
           <<"]ms , 1s = 1000ms"<<std::endl;
  // 加密结束
  LOG("Data has been encrypted.");

  create_encrypted_file(encrypt, public_key);
  LOG("Encrypted file has been created.");

  decrypt = (char *)malloc(encrypt_length);
  // 解密开始
  auto start2 = std::chrono::system_clock::now();
  int decrypt_length = private_decrypt(encrypt_length, (unsigned char*)encrypt, (unsigned char*)decrypt, private_key, RSA_PKCS1_OAEP_PADDING);
  auto end2 = std::chrono::system_clock::now();
  std::cout<<"解密花费 ["<<
           (std::chrono::time_point_cast<std::chrono::duration<int,std::ratio<1,1000>>>(end2)-
            std::chrono::time_point_cast<std::chrono::duration<int,std::ratio<1,1000>>>(start2)).count()/* return ms,1s=1000ms*/
           <<"]ms , 1s = 1000ms"<<std::endl;
  // 解密结束
  if(decrypt_length == -1) {
    LOG("An error occurred in private_decrypt() method");
  }
  LOG("Data has been decrypted.");

  FILE *decrypted_file = fopen("decrypted_file.txt", "w");
  fwrite(decrypt, sizeof(*decrypt), decrypt_length - 1, decrypted_file);
  fclose(decrypted_file);
  LOG("Decrypted file has been created.");

  RSA_free(keypair);
  free(private_key);
  free(public_key);
  free(encrypt);
  free(decrypt);
  BN_free(bne);
  LOG("OpenSSL_RSA has been finished.");
};

};// namespace method_4_rsa

#endif //OPENSSL_3_0_0_TEST_METHOD_4_RSA_H
