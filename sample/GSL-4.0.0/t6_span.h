//
// Created by shecannotsee on 24-2-1.
//

#ifndef T6_SPAN_H
#define T6_SPAN_H

#include "global_test_set.h"

namespace t6_span {

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t6_span::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t6_span::run] >>> done" << RESET_COLOR << "\n\n"; });

  int arr[] = {1, 2, 3, 4, 5};
  // &arr
  const gsl::span<int> my_span(arr, 5);
  // print
  std::cout << "Span size: " << my_span.size() << std::endl;
  std::cout << "Span elements:";
  for (const int num : my_span) {
    std::cout << " " << num;
  }
  std::cout << std::endl;

  // modify
  arr[2] = 100;
  // check
  std::cout << "Modified span elements:";
  for (const int num : my_span) {
    std::cout << " " << num;
  }
  std::cout << std::endl;

  std::cout << "Span elements :";
  for (int i = 0; i < my_span.size(); i++) {
    std::cout << " " << gsl::at(my_span, i);
  }
  std::cout << std::endl;
}

}  // namespace t6_span

#endif  // T6_SPAN_H
