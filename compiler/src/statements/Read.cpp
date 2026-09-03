#include "statements/Read.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Read::parse_read(Parser &parser) {
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
  return std::make_unique<Read>();
}
void Read::generate(CodeGenContext &) {}
