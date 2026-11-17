#include "utils.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
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
void add_string_literal_instruction(LabelCounters &counter, Parser &parser) {
  for (size_t i = 0; i < str_datas.size(); i++) {
    auto temp_str_index = "str." + std::to_string(i);

    auto instr = std::make_unique<DataItem>(temp_str_index,
                                            std::string(str_datas[i]), -1);
    parser.add_instruction(std::move(instr));
  }
}
void add_system_call(CodeGenContext &context) {
  context.syscall << std::format(
      "_start:\n\tand rsp, -16\n\tcall main:\n\tsyscall\n\tret\n\tmov rdi, "
      "rax\n\tsyscall\n\tret\n\t__sys_exit\n\n");
  context.syscall << std::format(
      "__sys_exit:\n\tmov rax, 60\n\tsyscall\n\tret\n\n");

  context.syscall << std::format(
      "__sys_read:\n\tmov rdx, rsi\n\tmov rsi, rdi\n\tmov rdi, 1\n\tmov rax, "
      "1\n\tsyscall\n\tret\n\n");
  context.syscall << std::format(
      "__sys_write:\n\tmov rdx, rsi\n\tmov rsi, rdi\n\tmov rdi, 0\n\tmov rax, "
      "0\n\tsyscall\n\tret\n\n");
}
