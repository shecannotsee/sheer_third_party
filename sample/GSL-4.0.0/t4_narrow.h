//
// Created by shecannotsee on 24-2-1.
//

#ifndef T4_NARROW_H
#define T4_NARROW_H

#include "global_test_set.h"

namespace t4_narrow {

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t4_narrow::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t4_narrow::run] >>> done" << RESET_COLOR << "\n\n"; });

  // error process
  try {
    // 128 > (-127~127)
    constexpr int sourceValue  = 128;
    char targetValue = gsl::narrow<char>(sourceValue);
    // debug
    std::cout << "Source value: " << sourceValue << std::endl;
    std::cout << "Target value (char): " << static_cast<int>(targetValue) << std::endl;
  } catch (const gsl::narrowing_error& e) {
    // error debug
    std::cout << RED_COLOR << "int(128) to char(-127~127) error" << std::endl;
    std::cout << e.what() << std::endl << RESET_COLOR;
  }

  // Right process
  constexpr int sourceValue  = 127;
  char targetValue = gsl::narrow<char>(sourceValue);
  // debug
  std::cout << "Source value (int): " << sourceValue << std::endl;
  std::cout << "Target value (char): " << static_cast<int>(targetValue) << std::endl;
}

}  // namespace t4_narrow

#endif  // T4_NARROW_H
