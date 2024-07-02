//
// Created by shecannotsee on 23-11-23.
//

#ifndef T1_COMPRESS_DATA_H
#define T1_COMPRESS_DATA_H

#include <zip.h>
#include <zlib.h>

#include <cstring>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

namespace t1_compress_data {
/**
 * @brief 该方法仅对目录下的所有文件进行压缩,.zip文件中包含目录下的所有文件
 *
 * @param dir_path 文件所在目录
 * @param file_names 文件列表
 * @param password 压缩密码,不可为空
 * @param zip_file_path 压缩文件存放位置
 * @return 操作是否执行成功
 */
bool zip_files_with_pwd(const std::string& dir_path, const std::vector<std::string>& file_names,
                        const std::string& password, const std::string& zip_file_path) {
  zipFile zip_file = zipOpen(zip_file_path.c_str(), APPEND_STATUS_CREATE);
  if (zip_file == nullptr) {
    std::cerr << "Failed to open zip file: " << zip_file_path << std::endl;
    return false;
  }

  zip_fileinfo zip_file_info;
  memset(&zip_file_info, 0, sizeof(zip_fileinfo));

  for (const auto& file_name : file_names) {
    // Construct the full file path by concatenating the directory path and file name
    std::string full_file_path = dir_path + "/" + file_name;

    if (zipOpenNewFileInZip3(zip_file, file_name.c_str(), &zip_file_info, nullptr, 0, nullptr, 0, nullptr,
                                Z_DEFLATED, Z_DEFAULT_COMPRESSION, 0, -MAX_WBITS, DEF_MEM_LEVEL, Z_DEFAULT_STRATEGY,
                                password.c_str(), 0) != ZIP_OK) {
      std::cerr << "Failed to open file in zip with password: " << full_file_path << std::endl;
      zipClose(zip_file, nullptr);
      return false;
                                }
    std::ifstream input_file(full_file_path, std::ios::binary);
    if (!input_file.is_open()) {
      std::cerr << "Failed to open input file: " << full_file_path << std::endl;
      zipClose(zip_file, nullptr);
      return false;
    }
    const int buffer_size = 4096;
    char buffer[buffer_size];

    while (input_file.good()) {
      sleep(2);

      input_file.read(buffer, buffer_size);
      zipWriteInFileInZip(zip_file, buffer, static_cast<unsigned int>(input_file.gcount()));
    }
    input_file.close();
    zipCloseFileInZip(zip_file);
  }

  zipClose(zip_file, nullptr);
  return true;
}

void main() {
  goto p3;
  /* single file */ {
    p1:
    const std::string dir_path      = ".."; // Replace with your directory path
    const std::vector<std::string> file_names = {"single_test_file.txt"}; // Add your file names
    const std::string password      = "789";
    const std::string zip_file_path = "../temp/single_test.zip";

    if (!zip_files_with_pwd(dir_path, file_names, password, zip_file_path)) {
      std::cout << "single file process failed.\n";
    } else {
      std::cout << "single file process success.\n";
    }
  }
  /* zip just include file */ {
    p2:
    const std::string dir_path      = "../test_dir"; // Replace with your directory path
    const std::vector<std::string> file_names = {"test_file1.txt", "test_file2.txt", "test_file3.txt"}; // Add your file names
    const std::string password      = "789";
    const std::string zip_file_path = "../temp/file.zip";

    if (!zip_files_with_pwd(dir_path, file_names, password, zip_file_path)) {
      std::cout << "file process failed.\n";
    } else {
      std::cout << "file process success.\n";
    }
  }
p3:
  /* zip include dir */ {
    // std::thread delete_thread([]() {
    //   const std::string file_path = "../test_dir/test_delete.txt";
    //   sleep(1);
    //   if (std::remove(file_path.c_str()) != 0) {
    //     std::cout << "File deletion failed: %s" << file_path.c_str() << std::endl;
    //     } else {
    //       std::cout << "Successfully deletion: %s" << file_path.c_str() << std::endl;
    //     }
    // });
    // std::thread write_thread([]() {
    //   const std::string file_path = "../test_dir/test_delete.txt";
    //   std::ofstream file_stream(file_path, std::ios::app);  // 使用 std::ios::app 表示在文件末尾追加内容
    //   if (!file_stream.is_open()) {
    //       std::cerr << "无法打开文件: " << file_path << std::endl;
    //       return 1;  // 返回错误代码
    //   }
    //   // 持续往文件中写入内容
    //   while (true) {
    //       std::string content = "1";
    //       file_stream << content << std::endl;
    //   }
    // });
    const std::string dir_path      = "/home/shecannotsee/desktop/all_code/sheTestcode/openssl1.1.1s_test/test_dir"; // Replace with your directory path
    const std::vector<std::string> file_names = {"test_delete.txt", "test_file1.txt"}; // Add your file names
    const std::string password      = "123456789";
    const std::string zip_file_path = "/home/shecannotsee/desktop/all_code/sheTestcode/openssl1.1.1s_test/temp/dir.zip";

    if (!zip_files_with_pwd(dir_path, file_names, password, zip_file_path)) {
      std::cout << "file process failed.\n";
    } else {
      std::cout << "file process success.\n";
    }
    // write_thread.join();
    // delete_thread.join();
  }
}

}  // namespace t1_compress_data

#endif  // T1_COMPRESS_DATA_H
