#include <iostream>
#include <string_view>
#include <magic_enum.hpp>

enum class Color { RED, GREEN, BLUE };

void print_color(Color color) {
  auto color_name = magic_enum::enum_name(color);
  std::cout << "Color: " << color_name << std::endl;
}

Color get_color_from_string(const std::string_view color_name) {
  auto color_opt = magic_enum::enum_cast<Color>(color_name);
  if (color_opt.has_value()) {
    return color_opt.value();
  }
  throw std::invalid_argument("Invalid color name");
}

int main() {
  // 将枚举值转换为字符串
  print_color(Color::RED);
  print_color(Color::GREEN);
  print_color(Color::BLUE);

  // 从字符串转换为枚举值
  try {
    Color color = get_color_from_string("GREEN");
    print_color(color);
  } catch (const std::invalid_argument& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
