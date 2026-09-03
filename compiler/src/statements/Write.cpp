#include "statements/Write.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Write::parse_write(Parser &parser) {
  parser.advance();
  if (!parser.expect(TokenName::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::IDENTIFIER, error::ExpectedIdentifier)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::COMMA, error::ExpectedComma)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::IDENTIFIER, error::ExpectedIdentifier)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenName::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }
  return std::make_unique<Write>();
}

void Write::generate(CodeGenContext &) {}
