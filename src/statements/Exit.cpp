#include "statements/Exit.hpp"
#include "token.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
std::unique_ptr<Statements> Exit::parse_exit(Parser &parser) {
  switch (parser.peek_token_name()) {
  case TokenName::LEFT_PAREN: {
    return parse_exit_with_braces(parser);
  }
  case TokenName::INT_LITERAL: {
    return parse_exit_without_braces(parser);
  }
  default:
    return nullptr;
  }
};

std::unique_ptr<Statements> Exit::parse_exit_with_braces(Parser &parser) {
  parser.consume_token();
  if (!parser.expect_token(TokenName::INT_LITERAL)) {
    return nullptr;
  }
  int dummy_exit_code = 1;
  {
    std::string string(parser.peek_token().value);
    try {
      dummy_exit_code = std::stoi(string);
    } catch (...) {
      dummy_exit_code = 1;
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
  std::cout << "suraj\n";

  return std::make_unique<Exit>(dummy_exit_code);
}
std::unique_ptr<Statements> Exit::parse_exit_without_braces(Parser &parser) {
  parser.consume_token();
  if (!parser.expect_token(TokenName::INT_LITERAL)) {
    return nullptr;
  }
  int dummy_exit_code = 1;
  {
    std::string string(parser.peek_token().value);
    try {
      dummy_exit_code = std::stoi(string);
    } catch (...) {
      dummy_exit_code = 1;
    }
  }

  parser.consume_token();

  if (!parser.expect_token(TokenName::SEMICOLON)) {
    return nullptr;
  }
  parser.consume_token();
  std::cout << "suraj\n";

  return std::make_unique<Exit>(dummy_exit_code);
}
void Exit::generate(std::stringstream &ss) {
  std::cout << "suraj\n";
  ss << "mov rdi, " << this->exitCode << "\n";
  ss << "mov rax, 60\n";
  ss << "syscall\n";
}
