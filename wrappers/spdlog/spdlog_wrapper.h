/**
 * @file spdlog_wrapper.h
 * @brief A logging utility class using spdlog for rotating file logs and console logs.
 *
 * This class provides an easy-to-use interface for registering loggers with rotating file sinks
 * and logging messages at various levels (info, warn, error, debug, critical).
 */
#ifndef SPDLOG_WRAPPER_H
#define SPDLOG_WRAPPER_H

#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_sinks.h>
#include <spdlog/spdlog.h>

#include <memory>
#include <unordered_map>

/**
 * @enum log_level
 * @brief Enum class representing different log levels supported by the spdlog_wrapper.
 */
enum class log_level {
  info,     ///< Informational messages that highlight the progress of the application.
  warn,     ///< Potentially harmful situations.
  error,    ///< Error events that might still allow the application to continue running.
  debug,    ///< Fine-grained informational events for debugging purposes.
  critical  ///< Severe error events that will presumably lead the application to abort.
};

/**
 * @class spdlog_wrapper
 * @brief A class that wraps around spdlog to provide an easy logging interface with file rotation.
 */
class spdlog_wrapper {
 public:
  spdlog_wrapper()  = default;  ///< Default constructor
  ~spdlog_wrapper() = default;  ///< Default destructor

 private:
  /**
   * @brief A map storing all registered loggers by name.
   *
   * The key is the logger's name, and the value is a shared pointer to the spdlog::logger instance.
   */
  std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> logger_registry_;  ///< log registry

 public:
  /**
   * @brief Logs a message to the console at the specified log level.
   *
   * This method is static, and thus can be used without creating an instance of spdlog_wrapper.
   *
   * @tparam level The log level at which the message will be logged (info, warn, error, debug, critical).
   * @tparam Args The types of the message format and arguments.
   * @param args The message format and arguments.
   */
  template <log_level level, typename... Args>
  static void console(Args&&... args) {
    if constexpr (level == log_level::info) {
      spdlog::info(std::forward<Args>(args)...);
    } else if constexpr (level == log_level::warn) {
      spdlog::warn(std::forward<Args>(args)...);
    } else if constexpr (level == log_level::error) {
      spdlog::error(std::forward<Args>(args)...);
    } else if constexpr (level == log_level::debug) {
      spdlog::debug(std::forward<Args>(args)...);
    } else if constexpr (level == log_level::critical) {
      spdlog::critical(std::forward<Args>(args)...);
    }
  }

  /**
   * @brief Registers and retrieves a rotating file logger by name.
   *
   * If a logger with the specified name already exists, it is returned.
   * Otherwise, a new logger is created, registered, and returned.
   *
   * @param logger_name The unique name of the logger.
   * @return A shared pointer to the registered logger instance.
   */
  auto register_logger(const std::string& logger_name) -> std::shared_ptr<spdlog::logger> {
    const std::string file_name = logger_name + ".log";
    // check existing logger
    if (const auto it = logger_registry_.find(logger_name); it != logger_registry_.end()) {
      // Already registered, return existing logger
      return it->second;
    }
    // set single size for file: 5MB，max file sum:4
    constexpr size_t max_file_size = 1024 * 1024 * 5;  // 5MB
    constexpr size_t max_files     = 4;
    // create logger
    logger_registry_[logger_name] = spdlog::rotating_logger_mt(logger_name, file_name, max_file_size, max_files);
    return logger_registry_[logger_name];
  }
};

#endif  // SPDLOG_WRAPPER_H
