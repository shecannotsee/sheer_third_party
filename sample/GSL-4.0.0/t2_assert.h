//
// Created by shecannotsee on 24-2-1.
//

#ifndef T2_ASSERT_H
#define T2_ASSERT_H

#include "global_test_set.h"

namespace t2_assert {

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t2_assert::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t2_assert::run] >>> done" << RESET_COLOR << "\n\n"; });

  int height = 1;
  int width  = 1;
  try {
    Expects(height > 0 && width > 0);
    std::cout << "t2_assert:" << __LINE__ << std::endl;
  } catch (...) {
    std::cout << "t2_assert:" << __LINE__ << std::endl;
  }

  try {
    Ensures(height + width == 2);
    std::cout << "t2_assert:" << __LINE__ << std::endl;
  } catch (...) {
    std::cout << "t2_assert:" << __LINE__ << std::endl;
  }
}

}  // namespace t2_assert

#endif  // T2_ASSERT_H
