#include <iostream>

#include "t1_qml_display_test.h"
#include "t2_event_test.h"
#include "t3_login_test.h"
#include "t4_more_qml_windows_switch_test.h"

int main(int argc, char *argv[]) {
  std::cout << "\033[33m" << "test start" << "\033[0m" << std::endl;

//  t1_qml_display_test::main(argc, argv);
//  t2_event_test::main(argc, argv);
//  t3_login_test::main(argc, argv);
  t4_more_qml_windows_switch_test::main(argc,argv);

  std::cout << "\033[33m" << "test end" << "\033[0m" << std::endl;
  return 0;
}
