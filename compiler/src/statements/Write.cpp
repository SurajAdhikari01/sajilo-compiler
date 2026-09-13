#include "statements/Write.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Write::parse_write(Parser &parser) {
  auto write_stmt = std::make_unique<Write>();
  parser.advance();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  write_stmt->variable = Expression::parse_expression(parser);

  if (!write_stmt->variable) {
    return nullptr;
  }
  if (!parser.expect(TokenType::COMMA, error::ExpectedComma)) {
    return nullptr;
  }
  write_stmt->length = Expression::parse_expression(parser);

  if (!write_stmt->length) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }
  return write_stmt;
}

void Write::generate(CodeGenContext &) {}
