#include "statements/Bol.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

#include <string>
std::unique_ptr<Statements> Bol::parse_bol(Parser &parser) {
  // parser.consume_token();

  switch (parser.peek_token_name()) {
  case TokenName::STRING_LITERAL: {
    return parse_bol_string(parser);
  }
  case TokenName::IDENTIFIER: {
    return parse_bol_variable(parser);
  }
  default:
    return nullptr;
  }
};

std::unique_ptr<Statements> Bol::parse_bol_string(Parser &parser) {
  parser.consume_token();
  const Token &token = parser.get_current_token();
  std::string dummy_bol_text(token.value);

  if (!parser.expect_token(TokenName::SEMICOLON)) {
    return nullptr;
  }
  parser.consume_token();

  return std::make_unique<Bol>(dummy_bol_text);
}
std::unique_ptr<Statements> Bol::parse_bol_variable(Parser &parser) {
  return nullptr;
}
void Bol::generate(CodeGenContext &context) {
  std::string label = "str" + std::to_string(context.lable++); // str0
  context.data << label << " db \"" << this->bolText << "\" , 10\n"
               << label << "_len equ $ - " << label << "\n";

  context.code << "mov rax, 1\n"
               << "mov rdi, 1\n"
               << "mov rsi, " << label << "\n"
               << "mov rdx, " << label << "_len\n"
               << "syscall\n";
  // str0 db "hello world", 10
  // str0_len equ $ - str0
  // mov rax , 1
  // mov rdi , 1
  // mov rsi , str0
  // mov rex , str0_len
  // syscall
}
