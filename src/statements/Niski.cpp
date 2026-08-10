#include "statements/Niski.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>
std::unique_ptr<Statements> Niski::parse_niski(Parser &parser) {
  switch (parser.peek_token_name()) {
  case TokenName::LEFT_PAREN: {
    return parse_niski_with_braces(parser);
  }
  case TokenName::INT_LITERAL: {
    return parse_niski_without_braces(parser);
  }
  default:
    return nullptr;
  }
};

std::unique_ptr<Statements> Niski::parse_niski_with_braces(Parser &parser) {
  parser.consume_token();
  if (!parser.expect_token(TokenName::INT_LITERAL)) {
    return nullptr;
  }
  int dummy_niski_code = 1;
  {
    std::string string(parser.peek_token().value);
    try {
      dummy_niski_code = std::stoi(string);
    } catch (...) {
      dummy_niski_code = 1;
    }
  }
  parser.consume_token();

  if (!parser.expect_token(TokenName::RIGHT_PAREN)) {
    return nullptr;
  }
  parser.consume_token();
  if (!parser.expect_token(TokenName::SEMICOLON)) {
    return nullptr;
  }
  parser.consume_token();

  return std::make_unique<Niski>(dummy_niski_code);
}
std::unique_ptr<Statements> Niski::parse_niski_without_braces(Parser &parser) {
  parser.consume_token();
  if (!parser.expect_token(TokenName::INT_LITERAL)) {
    return nullptr;
  }
  int dummy_niski_code = 1;
  {
    std::string string(parser.peek_token().value);
    try {
      dummy_niski_code = std::stoi(string);
    } catch (...) {
      dummy_niski_code = 1;
    }
  }

  parser.consume_token();

  if (!parser.expect_token(TokenName::SEMICOLON)) {
    return nullptr;
  }
  parser.consume_token();

  return std::make_unique<Niski>(dummy_niski_code);
}
void Niski::generate(CodeGenContext &context) {
  std::cout << "suraj\n";
  context.code << "mov rdi, " << this->niskiCode << "\n"
               << "mov rax, 60\n"
               << "syscall\n";
}
