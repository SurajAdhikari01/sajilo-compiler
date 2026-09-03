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
  if (parser.match(TokenName::RIGHT_PAREN)) {
    return parameters;
  }

  while (true) {
    if (!parser.expect(TokenName::KEYWORD, error::ExpectedKeyword)) {
      return {};
    }
    if (!parser.expect(TokenName::IDENTIFIER, error::ExpectedIdentifier)) {
      return {};
    }
    if (!parser.match(TokenName::COMMA)) {
      break;
    }
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, error::ExpectedRightParen)) {
    return {};
  }
  return parameters;
}

std::unique_ptr<Statements> Function::parse_function(Parser &parser) {
  parser.advance();
  if (!parser.expect(TokenName::IDENTIFIER, error::ExpectedIdentifier)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  parse_parameter(parser);
  if (!parser.expect(TokenName::ARROW, error::ExpectedArrow)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::DEU, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::KEYWORD, error::ExpectedKeyword)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  TokenName temp_token;
  if (!parser.check_any_of({TokenName::LEFT_BRACE, TokenName::SEMICOLON},
                           &temp_token)) {
    return nullptr;
  }
  if (temp_token == TokenName::LEFT_BRACE) {
    Scope::parse_scope(parser);
  }

  return std::make_unique<Function>();
}

void Function::generate(CodeGenContext &) {}
