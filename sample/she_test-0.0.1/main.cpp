#include <she_test.h>

int main(int argc, char** argv) {
  // If you want to use other output methods, you need to manually implement and add instances
  she_test::details::register_center<>::init_and_run(argc, argv);
  return 0;
}
