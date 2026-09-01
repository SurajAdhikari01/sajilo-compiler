#include "statements/Read.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Read::parse_read(Parser &parser) {
  parser.advance();
  if (!parser.expect(TokenName::LEFT_PAREN, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::IDENTIFIER, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::COMMA, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::IDENTIFIER, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::RIGHT_PAREN, "")) {
    return nullptr;
  }
  if (!parser.expect(TokenName::SEMICOLON, "")) {
    return nullptr;
  }
  return std::make_unique<Read>();
}
void Read::generate(CodeGenContext &) {}
