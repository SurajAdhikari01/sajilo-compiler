#include "utils.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <format>
#include <iostream>

void print_error(const Parser &parser, std::string_view error_msg) {
  const auto &current_token = parser.current_token();
  const auto code = parser.get_lexer().get_code_line(current_token.line_number);
  const auto filename = parser.get_lexer().get_filename();
  std::string message =
      std::format("{}:{}: {}", filename, current_token.line_number, error_msg);
  std::cout << message << "\n";
  message.clear();
  message += std::format("    {}", code);
  std::cout << message << "\n";
};

void print_error(const Parser &parser, std::string_view error_msg,
                 const SourceLocation &loc) {
  const auto code = parser.get_lexer().get_code_line(loc.line);
  const auto filename = parser.get_lexer().get_filename();
  std::string message = std::format("{}:{}: {}", filename, loc.line, error_msg);
  std::cout << message << "\n";
  message.clear();
  message += std::format("    {}", code);
  std::cout << message << "\n";
}
