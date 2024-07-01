//
// Created by shecannotsee on 24-2-1.
//

#ifndef T1_ALGORITHMS_H
#define T1_ALGORITHMS_H

#include <functional>
#include <vector>

#include "global_test_set.h"

namespace t1_algorithms {

void run() noexcept {
  std::cout << YELLOW_COLOR << "[t1_algorithms::run] >>> start" << RESET_COLOR << std::endl;
  gsl::final_action<std::function<void()>> _(
      []() { std::cout << GREEN_COLOR << "[t1_algorithms::run] >>> done" << RESET_COLOR << "\n\n"; });
  /* example-1 */ {
    int source[] = {1, 2, 3, 4, 5};
    int destination[5];

    // 创建源span和目标span
    const gsl::span<int> src_span(source, 5);
    const gsl::span<int> dest_span(destination, 5);

    // 调用copy函数进行复制
    copy(src_span, dest_span);

    // 打印目标span
    std::cout << "destination span:";
    for (const int num : dest_span) {
      std::cout << " " << num;
    }
    std::cout << std::endl;
  }
  /* example-2 */ {
    std::vector<int> source = {1, 2, 3, 4, 5};
    std::vector<int> destination(5);  // 目标向量预先分配相同大小的空间

    const gsl::span<const int> src_span(source);
    const gsl::span<int> destination_span(destination);

    // 调用copy函数进行复制
    gsl::copy(src_span, destination_span);

    // 打印目标span
    std::cout << "destination span:";
    for (const int num : destination) {
      std::cout << " " << num;
    }
    std::cout << std::endl;
  }
}

}  // namespace t1_algorithms

#endif  // T1_ALGORITHMS_H
