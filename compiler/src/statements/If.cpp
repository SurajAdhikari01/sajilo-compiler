#include "statements/If.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "statements/Scope.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> If::parse_if(Parser &parser) {
  parser.advance();
  auto if_stmt = std::make_unique<If>();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if_stmt->condition = Expression::parse_expression(parser);
  if (!if_stmt->condition) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }

  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  if_stmt->if_block = Scope::parse_scope(parser);
  if (!if_stmt->if_block) {
    return nullptr;
  }

  if (!parser.match(TokenType::NATRA)) {
    return if_stmt;
  }
  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  if_stmt->else_block = Scope::parse_scope(parser);
  if (!if_stmt->else_block) {
    return nullptr;
  }

  return if_stmt;
}
