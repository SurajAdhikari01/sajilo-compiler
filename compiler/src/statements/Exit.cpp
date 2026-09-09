#import "statements/Exit.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> Exit::parse_return(Parser &parser) {
  TokenType temp_token;
  if (!parser.expect_any_of({TokenType::LEFT_PAREN, TokenType::IDENTIFIER}, "",
                            &temp_token)) {
    return nullptr;
  }
  if (temp_token == TokenType::LEFT_PAREN) {
    if (!parser.expect(TokenType::IDENTIFIER, error::ExpectedIdentifier)) {
      return nullptr;
    }
    if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
      return nullptr;
    }
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return std::make_unique<Exit>();
}

void Exit::generate(CodeGenContext &) {}
