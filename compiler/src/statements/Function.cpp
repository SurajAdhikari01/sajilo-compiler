#include "statements/Function.hpp"
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
    if (!parser.expect(TokenName::KEYWORD, "")) {
      return {};
    }
    if (!parser.expect(TokenName::IDENTIFIER, "")) {
      return {};
    }
    if (!parser.match(TokenName::COMMA)) {
      break;
    }
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, "")) {
    return {};
  }
  return parameters;
}

std::unique_ptr<Statements> Function::parse_function(Parser &parser) {
  parser.advance();
  if (!parser.expect(TokenName::IDENTIFIER, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::LEFT_PAREN, "")) {
    return nullptr;
  }
  parse_parameter(parser);
  if (!parser.expect(TokenName::ARROW, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::DEU, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::LEFT_PAREN, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::KEYWORD, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, "")) {
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
