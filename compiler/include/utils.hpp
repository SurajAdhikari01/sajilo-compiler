#pragma once
#include <iostream>
#include <string>
#include <string_view>
inline std::string string_view_to_string(std::string_view sv) {
  return std::string(sv);
}
inline void print_error(std::string_view error_msg) {
  std::cout << error_msg << std::endl;
}
