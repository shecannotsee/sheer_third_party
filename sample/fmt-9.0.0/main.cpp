#include <fmt/core.h>
#include <fmt/format.h>
#include <fmt/ranges.h>

#include <iostream>
#include <vector>

// Example structure to demonstrate custom formatting
struct Point {
  int x, y;
};

// Formatter specialization for Point structure
template <>
struct fmt::formatter<Point> {
  // Parse format specifier
  constexpr const char* parse(format_parse_context& ctx) {
    return ctx.begin();
  }

  // Format Point structure
  template <typename FormatContext>
  typename FormatContext::iterator format(const Point& p, FormatContext& ctx) {
    return format_to(ctx.out(), "({}, {})", p.x, p.y);
  }
};

int main() {
  // Basic usage of fmt
  fmt::print("Hello, {}!\n", "world");

  // Formatted string
  std::string s = fmt::format("The answer is {}.", 42);
  std::cout << s << std::endl;

  // Formatting with multiple arguments
  fmt::print("Hello, {0}! The answer is {1}.\n", "world", 42);

  // Formatting with named arguments
  fmt::print("Hello, {name}! The answer is {number}.\n", fmt::arg("name", "world"), fmt::arg("number", 42));

  // Formatting a vector
  std::vector<int> vec = {1, 2, 3, 4, 5};
  fmt::print("Vector: {}\n", vec);

  // Custom formatting for user-defined type
  Point p = {3, 4};
  fmt::print("Point: {}\n", p);

  return 0;
}
