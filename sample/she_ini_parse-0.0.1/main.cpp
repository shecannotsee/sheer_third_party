#include <ini_parse.h>
#include <string>
#include <iostream>

int main() {
  she::ini_parse entity("../parse_test.ini");
  auto sections = entity.get_all_section();
  auto v = entity.get("s4", "k1");
  std::cout << "[s4]k1: " << v << std::endl;
  std::cout << "quit safely" << std::endl;
  return 0;
}
