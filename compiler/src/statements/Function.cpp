#include "statements/Function.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "statements/Scope.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

std::optional<std::vector<ParameterDecl>> parse_parameter(Parser &parser) {

  std::vector<ParameterDecl> parameters;
  if (parser.match(TokenType::RIGHT_PAREN)) {
    return parameters;
  }

  ParameterDecl param;

  while (true) {
    if (!parser.check_any_of({TokenType::KEYWORD, TokenType::IDENTIFIER})) {
      print_error(parser, "");
      return {};
    }
    param.type.name = parser.current_token().value;
    param.type.data_type = get_datatypes(param.type.name);
    parser.advance();

    if (!parser.check(TokenType::IDENTIFIER)) {
      return {};
    }
    param.name = parser.current_token().value;
    parser.advance();

    parameters.push_back(param);
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
  auto func_stmt = std::make_unique<Function>();
  parser.advance();
  if (!parser.check(TokenType::IDENTIFIER)) {
    print_error(parser, error::ExpectedIdentifier);
    return nullptr;
  }
  func_stmt->func_name = parser.current_token().value;
  parser.advance();

  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }

  auto opt_parameter = parse_parameter(parser);
  if (!opt_parameter) {
    return nullptr;
  }
  func_stmt->parameters = std::move(*opt_parameter);

  if (!parser.expect(TokenType::ARROW, error::ExpectedArrow)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::DEU, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if (!parser.check_any_of({TokenType::KEYWORD, TokenType::IDENTIFIER})) {
    print_error(parser, error::ExpectedReturnType);
    return nullptr;
  }
  func_stmt->return_type.name = parser.current_token().value;
  func_stmt->return_type.data_type = get_datatypes(func_stmt->return_type.name);
  parser.advance();
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
