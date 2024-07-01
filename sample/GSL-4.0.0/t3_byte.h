//
// Created by shecannotsee on 24-2-1.
//

#ifndef T3_BYTE_H
#define T3_BYTE_H

#include "global_test_set.h"

namespace t3_byte {

template <class T>
void compare(gsl::byte input, T compare_objects) {
  if (static_cast<T>(input) == compare_objects) {
    // ...
  } else {
    std::cout << RED_COLOR << static_cast<int>(input) << " > compare failed with >" << static_cast<int>(compare_objects)
              << std::endl
              << RESET_COLOR;
  }
}

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t3_byte::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t3_byte::run] >>> done" << RESET_COLOR << "\n\n"; });

  constexpr auto _1 = static_cast<gsl::byte>(4);
  compare<unsigned char>(_1, 4);

  constexpr gsl::byte _2 = gsl::to_byte<0x00>();
  compare<unsigned char>(_2, 0x00);

  /* bitwise_operations */ {
    using namespace gsl;
    const byte b = to_byte<0xFF>();

    byte a = to_byte<0x00>();
    if ((b | a) != to_byte<0xFF>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (a != to_byte<0x00>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a |= b;
    if (a != to_byte<0xFF>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a = to_byte<0x01>();
    if ((b & a) != to_byte<0x01>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a &= b;
    if (a != to_byte<0x01>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    if ((b ^ a) != to_byte<0xFE>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    if (a != to_byte<0x01>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    a ^= b;
    if (a != to_byte<0xFE>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a = to_byte<0x01>();
    if (~a != to_byte<0xFE>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a = to_byte<0xFF>();
    if ((a << 4) != to_byte<0xF0>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if ((a >> 4) != to_byte<0x0F>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }

    a <<= 4;
    if (a != to_byte<0xF0>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    a >>= 4;
    if (a != to_byte<0x0F>()) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
  }

  /* to_integer */ {
    constexpr gsl::byte target = gsl::to_byte<0x12>();
    if (0x12 != gsl::to_integer<char>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<short>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<long>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<long long>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<unsigned char>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<unsigned short>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<unsigned long>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
    if (0x12 != gsl::to_integer<unsigned long long>(target)) {
      std::cout << RED_COLOR << __FILE__ << ":" << __LINE__ << std::endl << RESET_COLOR;
    }
  }
}

}  // namespace t3_byte

#endif  // T3_BYTE_H
