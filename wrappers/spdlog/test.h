#ifndef TEST_H
#define TEST_H

#include <fstream>

#include "spdlog_wrapper.h"

inline void spdlog_wrapper_test() {
    // Setup test parameters
    log::log_file = "test_log_file.log";
    log::test_log_file = "test_log_file.log";
    log::test_module_name = "test";

    // Clear any existing log files before the test
    std::remove(log::log_file.c_str());
    std::remove(log::test_log_file.c_str());

    // Test logger creation
    auto logger = log::get_logger("test_logger");
    if (logger) {
        std::cout << "Logger created successfully: " << logger->name() << std::endl;
    } else {
        std::cerr << "Failed to create logger." << std::endl;
        return;
    }

    // Log messages
    logger->info("This is an info message.");
    logger->warn("This is a warning message.");
    logger->error("This is an error message.");
    logger->debug("This is a debug message."); // Depending on log level, this may or may not be logged
    logger->critical("This is a critical message.");

    // Check if the log file is created and contains the messages
    std::ifstream log_file(log::log_file);
    if (!log_file.is_open()) {
        std::cerr << "Log file could not be opened." << std::endl;
        return;
    }

    std::string line;
    bool info_found = false;
    bool warn_found = false;
    bool error_found = false;
    bool debug_found = false;
    bool critical_found = false;

    while (std::getline(log_file, line)) {
        if (line.find("This is an info message.") != std::string::npos) {
            info_found = true;
        }
        if (line.find("This is a warning message.") != std::string::npos) {
            warn_found = true;
        }
        if (line.find("This is an error message.") != std::string::npos) {
            error_found = true;
        }
        if (line.find("This is a debug message.") != std::string::npos) {
            debug_found = true;
        }
        if (line.find("This is a critical message.") != std::string::npos) {
            critical_found = true;
        }
    }

    // Output results
    std::cout << "Test Results:" << std::endl;
    std::cout << "Info message found: " << (info_found ? "Yes" : "No") << std::endl;
    std::cout << "Warning message found: " << (warn_found ? "Yes" : "No") << std::endl;
    std::cout << "Error message found: " << (error_found ? "Yes" : "No") << std::endl;
    std::cout << "Debug message found: " << (debug_found ? "Yes" : "No") << std::endl;
    std::cout << "Critical message found: " << (critical_found ? "Yes" : "No") << std::endl;

    // Clean up log files after the test
    std::remove(log::log_file.c_str());
    std::remove(log::test_log_file.c_str());
}

#endif //TEST_H
