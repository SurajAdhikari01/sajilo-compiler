#include "statements/Manau.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "symbolTable.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <iostream>
#include <memory>
#include <ostream>

std::unique_ptr<Statements> Manau::parse_manau(Parser &parser) {
  std::unique_ptr<Manau> manau_stmt = std::make_unique<Manau>();
  parser.advance();

  if (parser.match(TokenType::COLON)) {
    if (!parser.expect(TokenType::CONST, "")) {
      return nullptr;
    }
    manau_stmt->isConst = true;
  }
  if (!parser.check_any_of({TokenType::KEYWORD, TokenType::IDENTIFIER})) {
    print_error(parser, "");
    return nullptr;
  }

  manau_stmt->data_type.name = parser.current_token().value;

  manau_stmt->data_type.data_type = get_datatypes(manau_stmt->data_type.name);
  parser.advance();

  if (!parser.check(TokenType::IDENTIFIER)) {
    return nullptr;
  }

  manau_stmt->name = parser.current_token().value;
  parser.advance();
  if (parser.match(TokenType::ASSIGN)) {
    manau_stmt->expr = Expression::parse_expression(parser);
    if (!manau_stmt->expr) {
      return nullptr;
    }
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return manau_stmt;
}
void Manau::generate(CodeGenContext &) {}
