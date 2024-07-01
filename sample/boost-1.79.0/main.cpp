#include <boost/regex.hpp>
#include <iostream>

int main() {
  // Input string
  std::string input = "Boost Libraries are awesome!";

  // Regular expression pattern
  boost::regex pattern("([a-zA-Z]+)");

  // Replace matched pattern with "C++"
  std::string result = boost::regex_replace(input, pattern, "C++");

  // Output the result
  std::cout << "Original string: " << input << std::endl;
  std::cout << "Modified string: " << result << std::endl;

  return 0;
}
