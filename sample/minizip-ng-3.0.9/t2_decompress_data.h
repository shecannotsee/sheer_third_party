//
// Created by shecannotsee on 23-11-23.
//

#ifndef T2_DECOMPRESS_DATA_H
#define T2_DECOMPRESS_DATA_H

#include <unzip.h>
#include <zlib.h>

#include <cstring>
#include <fstream>

namespace t2_decompress_data {
/**
 * @brief 该函数只针对zip压缩包中只有一个文件的zip文件，用来获取单个文件的内容
 * @param zip_file_path zip文件的位置
 * @param password 压缩密码
 * @return zip文件中单个文件的内容
 */
std::string unzip_file_with_pwd(const std::string& zip_file_path, const std::string& password) {
  unzFile zip_file = unzOpen(zip_file_path.c_str());
  if (zip_file == nullptr) {
    std::cerr << "Failed to open zip file: " << zip_file_path << std::endl;
    return {};
  }

  if (unzOpenCurrentFilePassword(zip_file, password.c_str()) != UNZ_OK) {
    std::cerr << "Failed to open zip file with password" << std::endl;
    unzClose(zip_file);
    return {};
  }

  unz_file_info file_info;
  if (unzGetCurrentFileInfo(zip_file, &file_info, nullptr, 0, nullptr, 0, nullptr, 0) != UNZ_OK) {
    std::cerr << "Failed to get file info from zip file" << std::endl;
    unzCloseCurrentFile(zip_file);
    unzClose(zip_file);
    return {};
  }

  char buffer[file_info.uncompressed_size];
  int read_size = unzReadCurrentFile(zip_file, buffer, file_info.uncompressed_size);
  if (read_size < 0) {
    std::cerr << "Failed to read data from zip file" << std::endl;
    unzCloseCurrentFile(zip_file);
    unzClose(zip_file);
    return {};
  }

  unzCloseCurrentFile(zip_file);
  unzClose(zip_file);

  return std::string(buffer, static_cast<size_t>(file_info.uncompressed_size));
}

void main() {
  const std::string file_path = "../temp/single_test.zip";
  const std::string password  = "789";
  auto content = unzip_file_with_pwd(file_path, password);
  std::cout << "single_test_file.txt content is :\n[" << content << "]" << std::endl;
}

}  // namespace t2_decompress_data

#endif  // T2_DECOMPRESS_DATA_H
