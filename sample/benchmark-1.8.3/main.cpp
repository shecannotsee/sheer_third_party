#include <iostream>

#include "t1_base.h"

int main(int argc, char** argv) {
  std::cout << "benchmark test start.\n";
  t1_base::main(argc, argv);
  std::cout << "benchmark test end.\n";
  return 0;
}
