#import "statements/Return.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

std::unique_ptr<Statements> Return::parse_return(Parser &parser) {
  parser.advance();
  auto return_stmt = std::make_unique<Return>();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  return_stmt->return_value = Expression::parse_expression(parser);

  if (!return_stmt->return_value) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return return_stmt;
}

void Return::generate(CodeGenContext &) {};
