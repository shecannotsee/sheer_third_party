//
// Created by shecannotsee on 23-4-25.
//

#ifndef ASIO_TEST_ASIO_TEST_M2_ASYNC_TIMER_TEST_H_
#define ASIO_TEST_ASIO_TEST_M2_ASYNC_TIMER_TEST_H_

namespace m2_async_timer_test {

void print(const asio::error_code& /*e*/) {
  std::cout << "Hello, world!" << std::endl;
}

void main() {
  asio::io_context io;
  asio::steady_timer t(io, asio::chrono::seconds(5));
  t.async_wait(&print);
  std::cout << "wait to async timer...\n";
  io.run();
}

};  // namespace m2_async_timer_test

#endif  // ASIO_TEST_ASIO_TEST_M2_ASYNC_TIMER_TEST_H_
