#include "statements/While.hpp"

#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "statements/Scope.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <ostream>

std::unique_ptr<Statements> While::parse_while(Parser &parser) {
  parser.advance();
  auto while_stmt = std::make_unique<While>();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  while_stmt->condition = Expression::parse_expression(parser);
  if (!while_stmt->condition) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }

  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  while_stmt->while_block = Scope::parse_scope(parser);
  if (!while_stmt->while_block) {
    return nullptr;
  }

  return while_stmt;
}
