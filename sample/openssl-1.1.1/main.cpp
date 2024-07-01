#include <openssl/rand.h>
#include <openssl/sha.h>

#include <cstring>
#include <iostream>

// 函数声明
void generateRandomBytes(unsigned char *buffer, size_t size);
void calculateSHA256(const unsigned char *data, size_t size, unsigned char *hash);

int main() {
  const int BUFFER_SIZE = 32;  // 生成的随机数字节数
  unsigned char randomBuffer[BUFFER_SIZE];
  unsigned char sha256Hash[SHA256_DIGEST_LENGTH];

  // 生成随机数
  generateRandomBytes(randomBuffer, BUFFER_SIZE);

  // 计算 SHA-256 哈希值
  calculateSHA256(randomBuffer, BUFFER_SIZE, sha256Hash);

  // 打印生成的随机数和SHA-256哈希值
  std::cout << "Generated random bytes:" << std::endl;
  for (int i = 0; i < BUFFER_SIZE; ++i) {
    std::cout << std::hex << (int)randomBuffer[i];
  }
  std::cout << std::endl;

  std::cout << "SHA-256 hash:" << std::endl;
  for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
    std::cout << std::hex << (int)sha256Hash[i];
  }
  std::cout << std::endl;

  return 0;
}

// 生成随机数的函数实现
void generateRandomBytes(unsigned char *buffer, size_t size) {
  RAND_bytes(buffer, size);
}

// 计算SHA-256哈希值的函数实现
void calculateSHA256(const unsigned char *data, size_t size, unsigned char *hash) {
  SHA256_CTX sha256;
  SHA256_Init(&sha256);
  SHA256_Update(&sha256, data, size);
  SHA256_Final(hash, &sha256);
}
