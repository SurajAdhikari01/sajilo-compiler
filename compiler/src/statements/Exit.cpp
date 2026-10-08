#import "statements/Exit.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> Exit::parse_exit(Parser &parser) {
  parser.advance();
  auto exit_stmt = std::make_unique<Exit>();
  exit_stmt->location.line = parser.current_token().line_number;
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
bool Exit::analyze_semantics(Parser &parser) {
  auto type = exit_expr->get_primitive_type();
  if (type == PRIMITIVE_DATA_TYPES::UNEXPECTED) {
    print_error(parser, error::UseOfUndefined, location);
    return false;
  }
  if (!is_compatible_datatype(PRIMITIVE_DATA_TYPES::INT, type)) {

    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }
  return true;
};
