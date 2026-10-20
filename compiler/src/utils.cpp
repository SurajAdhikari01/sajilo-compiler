#include "utils.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <format>
#include <iostream>

void print_error(Parser &parser, std::string_view error_msg) {
  const auto &current_token = parser.current_token();
  const auto code = parser.get_lexer().get_code_line(current_token.line_number);
  const auto filename = parser.get_lexer().get_filename();
  std::string message = std::format("{}:{}: {}\n", filename,
                                    current_token.line_number, error_msg);
  std::cout << message << "\n";
  parser.append_error_message(message);
  message.clear();
  message += std::format("    {}\n", code);
  std::cout << message << "\n";
  parser.append_error_message(message);
};

void print_error(Parser &parser, std::string_view error_msg,
                 const SourceLocation &loc) {
  const auto code = parser.get_lexer().get_code_line(loc.line);
  const auto filename = parser.get_lexer().get_filename();
  std::string message =
      std::format("{}:{}: {}\n", filename, loc.line, error_msg);
  std::cout << message << "\n";
  parser.append_error_message(message);
  message.clear();
  message += std::format("    {}\n", code);
  std::cout << message << "\n";
  parser.append_error_message(message);
}
