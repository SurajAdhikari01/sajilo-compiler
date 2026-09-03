#pragma once

#include <string>
#include <string_view>
inline std::string string_view_to_string(std::string_view sv) {
  return std::string(sv);
}
class Parser;
void print_error(const Parser &parser, std::string_view error_msg);
