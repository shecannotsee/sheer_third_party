//
// Created by shecannotsee on 23-4-25.
//
#include <iostream>

#include "m1_sync_timer_test.h"
#include "m2_async_timer_test.h"
#include "m3_sync_tcp_demo.h"

int main(int argc, char* argv[]) {
  std::cout << "asio test start.\n";

  m1_sync_timer_test::main();
  m2_async_timer_test::main();
  m3_sync_tcp_demo::main(argc, argv);

  std::cout << "asio test done.\n";
  return 0;
};