#include <iostream>

#include "t1_qwidget_display_test.h"
#include "t2_login_test.h"
#include "t3_chat_window_test.h"

int main(int argc, char *argv[]) {
  std::cout << "\033[33m" << "test start" << "\033[0m" << std::endl;

//  t1_qwidget_display_test::main(argc, argv);
//  t2_login_test::main(argc, argv);
  t3_chat_window_test::main(argc, argv);

  std::cout << "\033[33m" << "test end" << "\033[0m" << std::endl;
  return 0;
}
