#include <glog/logging.h>

int main(int argc, char* argv[]) {
  // 初始化 Google 日志库
  google::InitGoogleLogging(argv[0]);

  // 设置日志级别，此处设置为 INFO 级别
  FLAGS_logtostderr = 1;             // 输出到标准错误流
  FLAGS_minloglevel = google::INFO;  // 设置最低日志级别为 INFO

  // 记录日志
  LOG(INFO) << "This is an informational message";
  LOG(WARNING) << "This is a warning message";
  LOG(ERROR) << "This is an error message";

  // 停止 Google 日志库
  google::ShutdownGoogleLogging();

  return 0;
}
