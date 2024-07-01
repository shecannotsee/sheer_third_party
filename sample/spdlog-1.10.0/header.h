//
// Created by shecannotsee on 2022/10/18.
//
#ifndef SHETESTCODE_SPDLOG_TEST_HEADER_H_
#define SHETESTCODE_SPDLOG_TEST_HEADER_H_

#include <chrono>
#include "spdlog/spdlog.h"//_st means singe thread; _mt means many threads
#include "spdlog/sinks/stdout_color_sinks.h"// support for stdout_color_mt
#include "spdlog/sinks/basic_file_sink.h"// support for basic_logging_mt
#include "spdlog/sinks/rotating_file_sink.h"// support for rotating_logger_mt
#include "spdlog/sinks/daily_file_sink.h"// support for daily_logger_mt

// base test
namespace method1 {
void main() {
  // Create a daily logger - a new file is created every day on 2:30am
  auto logger = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt", 0, 0);
  // write to logfile every 5s
  spdlog::flush_every (std::chrono::seconds(5));
  // 按照指定级别实时刷新到日志系统中
  logger->flush_on(spdlog::level::trace);
  //普通信息
  logger->info("Welcome to spdlog!");
  //浮点数
  logger->warn("Support for floats {:03.2f}", 1.23456);
  //多个字符串参数
  logger->warn("Positional args are {1} {0}..", "too", "supported");
  //单个参数
  logger->error("Some error message with arg: {}", 1);
  //左对齐
  logger->error("{:<30}", "left aligned");
  //整形的十进制，十六进制，八进制，二进制
  logger->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 42);
  //会在同一个日志文件下添加日志
  auto logger2 = spdlog::daily_logger_mt("other","logs/daily.txt",0,0);
  logger2->info("Welcome to spdlog!");
}
};//namespace method1

// log type test
namespace method2 {
void main() {
  /* cmd out */ {
    auto logger_cmd = spdlog::stdout_color_mt("stdout_color");
    logger_cmd->info("success");
    logger_cmd->error("failed.");
  };
  /* single log file */ {
    auto logger_basic = spdlog::basic_logger_mt("basic_logger", "logs/basic_log.txt");
    logger_basic->info("hello {}!block11",   "world");
  };
  /* Limit file size log */ {
    auto logger_rota = spdlog::rotating_logger_mt(
        "rotating_logger",
        "logs/rotating_logger.txt",
        1024*1024*5,/* The size of a single file is 5mb */
        10/* 10 5mb files */);

    //for (int i=0;i<1000000;++i) logger_rota->info("ass");
  };
  /* daily log */ {
    auto logger_daily = spdlog::daily_logger_mt("daily_logger", "logs/daily.txt",0,0);
    logger_daily->info("daily log");
  };
  // use get to get an already created logger, like single case
  auto logger = spdlog::get("daily_logger");
  logger->info("get in other where");
};
};//namespace method2

// log flush test
namespace method3 {
void main() {
  //flush test
  auto logger = spdlog::basic_logger_mt("async test", "logs/async_log.txt");
  /* set [Time interval] to write files from buffer*/ {
    spdlog::flush_every(std::chrono::minutes (1));
    spdlog::flush_every(std::chrono::seconds (1));
    spdlog::flush_every(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::milliseconds(1)));// 毫秒,千分之一秒
    spdlog::flush_every(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::microseconds(1)));// 微秒,百万分之一秒
    spdlog::flush_every(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::nanoseconds(1)));// 纳秒,十亿分之一秒

    spdlog::flush_every(std::chrono::seconds (10));// The last setting takes effect
  }
  logger->info("now");
  sleep(1);
  logger->info("now sleep");// log time +1s
  int n;std::cin>>n;
};
};//namespace method3

// level and flush test
namespace method4 {
void main() {
  // global level is info,info can wirite info,warn,error,critical
  auto logger = spdlog::basic_logger_mt("basic","logs/method4_log.txt");
  spdlog::set_level(spdlog::level::trace);// need to set global level and logger can write
  spdlog::flush_on(spdlog::level::critical);// real time refresh
  // spdlog::set_level(spdlog::level::debug);// default write level is info(global default level)
  //logger->flush_on(spdlog::level::critical);// real time refresh
  logger->trace("trace level");// not write
  logger->debug("debug level");// not write
  logger->info("info level");// write
  logger->warn("warn level");// write
  logger->error("error level");// write
  logger->critical("critical level");// write
  int n;std::cin>>n;

}
};//namespace method4

#endif //SHETESTCODE_SPDLOG_TEST_HEADER_H_
