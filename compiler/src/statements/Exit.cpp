#import "statements/Exit.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> Exit::parse_exit(Parser &parser) {
  parser.advance();
  auto exit_stmt = std::make_unique<Exit>();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  exit_stmt->exit_expr = Expression::parse_expression(parser);
  if (!exit_stmt->exit_expr) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return exit_stmt;
}

void Exit::generate(CodeGenContext &) {}
bool Exit::analyze_semantics() {
  auto primary_expr = dynamic_cast<PrimaryExpression *>(exit_expr.get());
  if (!primary_expr) {
    return false;
  }
  if (primary_expr->primary_type ==
      PrimaryExpression::PRIMARY_TYPE::INT_LITERAL) {
    return true;
  }

  return false;
};
