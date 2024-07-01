//
// Created by shecannotsee on 24-2-1.
//

#ifndef T5_POINTERS_H
#define T5_POINTERS_H

#include "global_test_set.h"

namespace t5_pointers {

// 使用 gsl::owner 作为函数返回类型
inline gsl::owner<int*> create_int_42() {
  return new int(42);
}

// 使用 gsl::not_null 作为函数参数类型
inline void print_value(const gsl::not_null<int*> ptr) {
  std::cout << "Value: " << *ptr << std::endl;
}

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t5_pointers::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t5_pointers::run] >>> done" << RESET_COLOR << "\n\n"; });

  // Use gsl::owner as the pointer type
  gsl::owner<int*> ptr = create_int_42();
  auto release         = gsl::finally([&]() {
    if (ptr == nullptr) {
      std::cout << RED_COLOR << "ptr error\n" << RESET_COLOR;
    } else {
      delete ptr;
      std::cout << "release ptr success.\n";
    }
  });

  // Use gsl::not_null as the pointer type
  gsl::not_null<int*> not_null_ptr = gsl::make_not_null(ptr);
  print_value(not_null_ptr);

  // Use gsl::strict_not_null as the pointer type
  gsl::strict_not_null<int*> strict_not_null_ptr = gsl::make_strict_not_null(ptr);
  print_value(strict_not_null_ptr);
}

}  // namespace t5_pointers

#endif  // T5_POINTERS_H
