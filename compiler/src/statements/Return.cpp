#import "statements/Return.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> Return::parse_return(Parser &parser) {
  TokenName temp_token;
  if (!parser.expect_any_of({TokenName::LEFT_PAREN, TokenName::IDENTIFIER}, "",
                            &temp_token)) {
    return nullptr;
  }
  if (temp_token == TokenName::LEFT_PAREN) {
    if (!parser.expect(TokenName::IDENTIFIER, error::ExpectedIdentifier)) {
      return nullptr;
    }
    if (!parser.expect(TokenName::RIGHT_PAREN, error::ExpectedRightParen)) {
      return nullptr;
    }
  }
  if (!parser.expect(TokenName::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return std::make_unique<Return>();
}

void Return::generate(CodeGenContext &) {}
