/**
 * @file spdlog_wrapper.h
 * @brief Logging utility wrapper for `spdlog` with support for both production and test logging.
 *
 * This header provides a wrapper around the `spdlog` logging library, facilitating the creation of
 * daily and rotating log files, as well as console outputs. It distinguishes between regular
 * production logging and special test logging, each with its own configuration and logging levels.
 *
 * @author shecannotsee
 * @date 2024-10-23
 */
#ifndef SPDLOG_WRAPPER_H
#define SPDLOG_WRAPPER_H

#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>

/**
 * @class spdlog_wrapper
 * @brief Provides static methods to manage logging with `spdlog`.
 *
 * The `spdlog_wrapper` class offers static utility methods to obtain a logger instance, manage log levels,
 * and configure logging outputs for both production and test scenarios. The class supports both
 * rotating log files and console output, using `spdlog`.
 */
class spdlog_wrapper {
 public:
  /**
   * @brief Deleted default constructor to prevent instantiation.
   */
  spdlog_wrapper() = delete;

  /** @brief The log file path for production logs. */
  static std::string log_file;

  /** @brief The log file path for test logs. */
  static std::string test_log_file;

  /** @brief The module name used for test logging. */
  static std::string test_module_name;

  /**
   * @brief Retrieves a logger instance.
   *
   * If the given name matches the test module name, a logger configured for testing is returned.
   * Otherwise, a regular production logger is created.
   *
   * @param name The name of the logger.
   * @return A shared pointer to the requested logger.
   */
  static auto get_logger(const std::string& name) -> std::shared_ptr<spdlog::logger> {
    if (name == test_module_name) {
      static const std::shared_ptr<spdlog::logger> INSTANCE = create_test_logger();
      return INSTANCE;
    }
    return create_logger(name);
  }

  /**
   * @brief Logs messages to the console at the specified log level.
   *
   * This template method logs messages at various log levels such as info, warn, error, debug,
   * and critical, using `spdlog`. The log level is specified via the `level` template parameter.
   *
   * @tparam level The logging level from `spdlog::level::level_enum`.
   * @tparam Args The argument types for the message to be logged.
   * @param args The arguments for the log message.
   */
  template <spdlog::level::level_enum level, typename... Args>
  static void console(Args&&... args) {
    using namespace spdlog::level;
    if constexpr (level == info) {
      spdlog::info(std::forward<Args>(args)...);
    } else if constexpr (level == warn) {
      spdlog::warn(std::forward<Args>(args)...);
    } else if constexpr (level == err) {
      spdlog::error(std::forward<Args>(args)...);
    } else if constexpr (level == debug) {
      spdlog::debug(std::forward<Args>(args)...);
    } else if constexpr (level == critical) {
      spdlog::critical(std::forward<Args>(args)...);
    }
  }

 private:
  /** @brief Constant for megabytes, used in log file size calculations. */
  static constexpr int MB = 1024 * 1024;

  /**
   * @brief Creates or retrieves a rotating file logger.
   *
   * This method creates a rotating logger that writes to `log_file`. The log file size is limited
   * to 5 MB with up to 3 backup files maintained.
   *
   * @param name The name of the logger.
   * @return A shared pointer to the logger.
   */
  static auto create_logger(const std::string& name) -> std::shared_ptr<spdlog::logger> {
    auto logger = spdlog::get(name);
    if (!logger) {
      logger = spdlog::rotating_logger_mt(name, log_file, 5 * MB, 3);
    }
    return logger;
  }

  /**
   * @brief Creates or retrieves a logger specifically for test logging.
   *
   * This logger is configured to write logs both to the console and to a rotating log file
   * (`test_log_file`) of up to 1 MB with 2 backup files maintained. The log level for this logger
   * is set to `trace` to capture detailed logs.
   *
   * @param name The name of the logger, defaults to `test_module_name`.
   * @return A shared pointer to the test logger.
   */
  static auto create_test_logger(const std::string& name = test_module_name) -> std::shared_ptr<spdlog::logger> {
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(std::make_shared<spdlog::sinks::stdout_sink_st>());
    sinks.push_back(std::make_shared<spdlog::sinks::rotating_file_sink_st>(test_log_file, 1 * MB, 2));
    auto combined_logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
    register_logger(combined_logger);
    combined_logger->set_level(spdlog::level::trace);
    return combined_logger;
  }
};

/** @brief Default log file path for production logging. */
std::string spdlog_wrapper::log_file = "log_file.log";

/** @brief Default log file path for test logging. */
std::string spdlog_wrapper::test_log_file = "test_log_file.log";

/** @brief Default module name used for test logging. */
std::string spdlog_wrapper::test_module_name = "test";

#endif  // SPDLOG_WRAPPER_H
