#include "statements/Read.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Read::parse_read(Parser &parser) {
  auto read_stmt = std::make_unique<Read>();
  parser.advance();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  read_stmt->variable = Expression::parse_expression(parser);
  if (!read_stmt->variable) {
    return nullptr;
  }

  if (!parser.expect(TokenType::COMMA, error::ExpectedComma)) {
    return nullptr;
  }
  read_stmt->length = Expression::parse_expression(parser);
  if (!read_stmt->length) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }
  return read_stmt;
}
void Read::generate(CodeGenContext &) {}
