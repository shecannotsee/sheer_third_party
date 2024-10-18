#ifndef TEST_H
#define TEST_H

#include "spdlog_wrapper.h"

inline void spdlog_wrapper_test() {
  using log = spdlog_wrapper;
  log::console<log_level::info>("This is an info message.");
  log::console<log_level::warn>("This is a warning message.");
  log::console<log_level::error>("This is an error message with parameter: {}", 42);
  log::console<log_level::debug>("Debugging info: {}", "value");
  log::console<log_level::critical>("Critical error occurred!");
  spdlog::set_level(spdlog::level::debug);
  log::console<log_level::debug>("Debugging info: {}", "value");

  spdlog_wrapper logger;
  const auto p = logger.register_logger("test");
  p->info("This is an info message.");
  p->warn("This is a warning message.");
  p->error("This is an error message with parameter: {}", 42);
  p->debug("This is an error message with parameter: {}", 42);
  p->critical("This is an critical error occurred!");


}

#endif //TEST_H
