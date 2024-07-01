//
// Created by shecannotsee on 24-2-1.
//

#ifndef T8_UTIL_H
#define T8_UTIL_H

#include <functional>

#include "global_test_set.h"

namespace t8_util {

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t8_util::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t8_util::run] >>> done" << RESET_COLOR << "\n\n"; });

  auto __ = gsl::finally(
      []() { std::cout << GREEN_COLOR << "[t8_util::run] >>> done, from gsl::finally" << RESET_COLOR << "\n"; });

  std::cout << __LINE__ << std::endl;
  std::cout << "t8_util run test." << std::endl;
}

}  // namespace t8_util

#endif  // T8_UTIL_H
