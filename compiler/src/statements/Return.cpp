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
  return_stmt->location.line = parser.current_token().line_number;
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  return_stmt->return_expr = Expression::parse_expression(parser);

  if (!return_stmt->return_expr) {
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
bool Return::analyze_semantics(Parser &parser) {

  auto type = return_expr->get_primitive_type();
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
