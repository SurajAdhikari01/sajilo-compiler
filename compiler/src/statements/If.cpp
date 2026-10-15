#include "statements/If.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/Scope.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <type_traits>

std::unique_ptr<Statements> If::parse_if(Parser &parser) {
  parser.advance();
  auto if_stmt = std::make_unique<If>();
  if_stmt->location.line = parser.current_token().line_number;
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

bool If::analyze_semantics(Parser &parser) {
  if (!condition->analyze_symantics(parser, location))
    return false;
  auto if_val = if_block->analyze_semantics(parser);
  if (!else_block)
    return if_val;
  return if_val && else_block->analyze_semantics(parser);
}
