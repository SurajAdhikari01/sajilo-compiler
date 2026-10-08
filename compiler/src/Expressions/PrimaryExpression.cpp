#include "Expression/PrimaryExpression.hpp"
#include "parser.hpp"
#include "symbolTable.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Expression> PrimaryExpression::parse_primary(Parser &parser) {
  TokenType tempToken;
  if (!parser.check_any_of({TokenType::INT_LITERAL, TokenType::STRING_LITERAL,
                            TokenType::IDENTIFIER},
                           &tempToken)) {
    return nullptr;
  }

  auto primary_expr = std::make_unique<PrimaryExpression>();
  if (tempToken == TokenType::INT_LITERAL) {
    primary_expr->primitive_data_type = PRIMITIVE_DATA_TYPES::INT;
    primary_expr->value = parser.current_token().value;
  } else if (tempToken == TokenType::STRING_LITERAL) {
    primary_expr->primitive_data_type = PRIMITIVE_DATA_TYPES::STRING;
    primary_expr->value = parser.current_token().value;
  } else if (tempToken == TokenType::IDENTIFIER) {
    primary_expr->primitive_data_type = PRIMITIVE_DATA_TYPES::IDENTIFIER;
    primary_expr->value = parser.current_token().value;
  }
  parser.advance();
  return primary_expr;
}
PRIMITIVE_DATA_TYPES PrimaryExpression::get_primitive_type() {
  if (primitive_data_type == PRIMITIVE_DATA_TYPES::IDENTIFIER) {
    auto data = get_table().lookup(value);
    if (!data) {
      return PRIMITIVE_DATA_TYPES::UNEXPECTED;
    }
    return data->type.data_type;
  }
  return primitive_data_type;
}
