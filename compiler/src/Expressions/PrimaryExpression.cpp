#include "Expression/PrimaryExpression.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Expression> PrimaryExpression::parse_primary(Parser &parser) {
  TokenType tempToken;
  if (!parser.match_any_of({TokenType::INT_LITERAL, TokenType::STRING_LITERAL,
                            TokenType::IDENTIFIER},
                           &tempToken)) {
    return nullptr;
  }
  auto primary_expr = std::make_unique<PrimaryExpression>();
  if (tempToken == TokenType::INT_LITERAL) {
    primary_expr->primary_type = PRIMARY_TYPE::INT_LITERAL;
    primary_expr->value = parser.current_token().value;
  } else if (tempToken == TokenType::STRING_LITERAL) {
    primary_expr->primary_type = PRIMARY_TYPE::STRING_LITERAL;
    primary_expr->value = parser.current_token().value;
  } else if (tempToken == TokenType::IDENTIFIER) {
    primary_expr->primary_type = PRIMARY_TYPE::IDENTIFIER;
    primary_expr->value = parser.current_token().value;
  }
  return primary_expr;
}
