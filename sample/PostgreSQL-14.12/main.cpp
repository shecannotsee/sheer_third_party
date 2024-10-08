//
// Created by shecannotsee on 23-10-9.
//
#include <iostream>

#include "t1_connect_test.h"
#include "t0_example.h"

const std::string RESET_COLOR   = "\033[0m";
const std::string RED_COLOR     = "\033[31m";
const std::string GREEN_COLOR   = "\033[32m";
const std::string YELLOW_COLOR  = "\033[33m";
const std::string PURPLE_COLOR  = "\033[35m";
const std::string BLUE_COLOR    = "\033[34m";

int main(int argc, char *argv[]) {
  std::cout << YELLOW_COLOR << "test start" << RESET_COLOR << std::endl;

  t0_example::demo1();
  t0_example::demo2();
  t1_connect_test::main();

  std::cout << YELLOW_COLOR << "test end" << RESET_COLOR << std::endl;
  return 0;
}
