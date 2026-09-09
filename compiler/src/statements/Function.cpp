#include "statements/Function.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "statements/Scope.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <optional>
#include <vector>

std::optional<std::vector<Parameters>> parse_parameter(Parser &parser) {
  std::vector<Parameters> parameters;
  if (parser.match(TokenType::RIGHT_PAREN)) {
    return parameters;
  }

  while (true) {
    if (!parser.expect(TokenType::KEYWORD, error::ExpectedKeyword)) {
      return {};
    }
    if (!parser.expect(TokenType::IDENTIFIER, error::ExpectedIdentifier)) {
      return {};
    }
    if (!parser.match(TokenType::COMMA)) {
      break;
    }
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return {};
  }
  return parameters;
}

std::unique_ptr<Statements> Function::parse_function(Parser &parser) {
  parser.advance();
  if (!parser.expect(TokenType::IDENTIFIER, error::ExpectedIdentifier)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  parse_parameter(parser);
  if (!parser.expect(TokenType::ARROW, error::ExpectedArrow)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::DEU, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::KEYWORD, error::ExpectedKeyword)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  TokenType temp_token;
  if (!parser.check_any_of({TokenType::LEFT_BRACE, TokenType::SEMICOLON},
                           &temp_token)) {
    return nullptr;
  }
  if (temp_token == TokenType::LEFT_BRACE) {
    Scope::parse_scope(parser);
  }

  return std::make_unique<Function>();
}

void Function::generate(CodeGenContext &) {}
