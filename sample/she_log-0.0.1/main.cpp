#include <she_log.h>

int main() {
  she_log::logger pen;
  {
    const auto local_file = std::make_shared<she_log::local_file>("./test_log.txt");
    local_file->set_format(she_log::log_format::SHE_LOG);
    local_file->set_level(she_log::log_level::ALL);
    const auto console = std::make_shared<she_log::console>();
    console->set_format(she_log::log_format::SHE_LOG);
    console->set_level(she_log::log_level::ALL);

    pen.add_output_method(local_file);
    pen.add_output_method(console);
  }

  for (int i = 0; i < 10; ++i) {
    auto msg = std::to_string(i + 1);
    pen.record<she_log::log_level::DEBUG>(she_log::fmt("this number is:{}, index:{}", msg, i));
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
