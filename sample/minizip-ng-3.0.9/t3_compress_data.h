//
// Created by shecannotsee on 23-11-23.
//

#ifndef T3_COMPRESS_DATA_H
#define T3_COMPRESS_DATA_H

#include <chrono>
#include <random>
#include <iomanip>
#include <dirent.h>

namespace t3_compress_data {

std::string getCurrentTimestamp() {
  auto now = std::chrono::system_clock::now();
  auto duration = now.time_since_epoch();
  auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

  // Convert milliseconds to time_t
  std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

  // Format time
  std::tm* timeInfo = std::localtime(&currentTime);

  // Create a time stamp string
  std::ostringstream oss;
  oss << std::put_time(timeInfo, "%Y%m%d%H%M%S") << milliseconds.count() % 1000;

  return oss.str();
}

std::string generateRandomString(int length = 10) {
  std::random_device rd;
  std::mt19937 gen(rd());

  const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::uniform_int_distribution<> distribution(0, characters.size() - 1);

  std::string randomString;
  randomString.reserve(length);

  for (int i = 0; i < length; ++i) {
    randomString += characters[distribution(gen)];
  }

  return randomString;
}

void createFile(const std::string& filePath, const std::string& fileName, const std::string& content) {
  // Concatenate file path and name
  std::string fullFilePath = filePath + "/" + fileName;
  // Create and open the file
  std::ofstream file(fullFilePath);
  // Write content to the file
  file << content;
  // Close the file
  file.close();
}

bool deleteFile(const std::string& filePath) {
  // Remove the file
  if (std::remove(filePath.c_str()) != 0) {
    // 删除失败
    std::cout << "delete failed.\n";
    return false;
  } else {
    // 删除成功
    std::cout << "delete success.\n";
    return true;
  }
}

void main() {
  for ( int i = 5 ; i >= 0 ; i-- ) {
    const std::string file_name = getCurrentTimestamp()+ generateRandomString();
    createFile("../",file_name,"99999");
    sleep(3);
    deleteFile(std::string("../") + file_name);
  }
}

}

#endif //T3_COMPRESS_DATA_H
