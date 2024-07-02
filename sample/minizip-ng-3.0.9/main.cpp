//
// Created by shecannotsee on 23-11-23.
//
#include <iostream>
// #include "openssl_aes.h"
#include "t1_compress_data.h"
#include "t2_decompress_data.h"
#include "t3_compress_data.h"

int main() {
  std::cout << "start.\n";

  t1_compress_data::main();
  t2_decompress_data::main();
  t3_compress_data::main();

  std::cout << "Done.\n";
  return 0;
}
