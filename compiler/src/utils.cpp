#include "utils.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <ostream>

void print_error(const Parser &parser, std::string_view error_msg) {
  const auto &current_token = parser.current_token();
  const auto line = parser.get_lexer().get_code_line(current_token.line_number);
  std::cout << line << std::endl;
  std::cout << error_msg << std::endl;
};
