#include "Expression/UnaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <initializer_list>
#include <memory>

UnaryExpression::UN_OPERATORS get_unary_operator_prefix(TokenType TokenType) {
  switch (TokenType) {
  case TokenType::AND:
    return UnaryExpression::UN_OPERATORS::REFERENCE;
  case TokenType::INCREMENT:
    return UnaryExpression::UN_OPERATORS::PRE_INCR;
  case TokenType::DECREMENT:
    return UnaryExpression::UN_OPERATORS::PRE_DECR;
  case TokenType::PLUS:
    return UnaryExpression::UN_OPERATORS::POSITIVE;
  case TokenType::MINUS:
    return UnaryExpression::UN_OPERATORS::NEGATIVE;
  case TokenType::STAR:
    return UnaryExpression::UN_OPERATORS::DEREFERENCE;
  case TokenType::NOT:
    return UnaryExpression::UN_OPERATORS::LOGICAL_NOT;
  case TokenType::BIT_NOT:
    return UnaryExpression::UN_OPERATORS::BITWISE_NOT;
  default:
    return UnaryExpression::UN_OPERATORS::NONE;
    ;
  }
}
UnaryExpression::UN_OPERATORS get_unary_operator_postfix(TokenType TokenType) {
  switch (TokenType) {
  case TokenType::INCREMENT:
    return UnaryExpression::UN_OPERATORS::POST_INCR;
  case TokenType::DECREMENT:
    return UnaryExpression::UN_OPERATORS::POST_DECR;
  default:
    return UnaryExpression::UN_OPERATORS::NONE;
  }
}

std::unique_ptr<Expression> UnaryExpression::parse_prefix(Parser &parser) {
  static const std::initializer_list<TokenType> unary_operator = {
      TokenType::INCREMENT, TokenType::DECREMENT, TokenType::BIT_NOT,
      TokenType::NOT,       TokenType::PLUS,      TokenType::MINUS,
      TokenType::STAR,      TokenType::AND,
  };
  TokenType tempToken;
  if (!parser.match_any_of(unary_operator, &tempToken)) {
    return nullptr;
  }
  auto unaryExpr = std::make_unique<UnaryExpression>();
  unaryExpr->un_operator = get_unary_operator_prefix(tempToken);
  unaryExpr->un_operand = Expression::parse_expression(parser);

  return unaryExpr;
}
std::unique_ptr<Expression>
UnaryExpression::parse_postfix(Parser &parser,
                               std::unique_ptr<Expression> operand) {

  static const std::initializer_list<TokenType> unary_operator = {
      TokenType::INCREMENT, TokenType::DECREMENT};
  TokenType tempToken;
  if (!parser.match_any_of(unary_operator, &tempToken)) {
    return nullptr;
  }
  auto unaryExpr = std::make_unique<UnaryExpression>();
  unaryExpr->un_operator = get_unary_operator_postfix(tempToken);
  unaryExpr->un_operand = Expression::parse_expression(parser);

  return unaryExpr;
}
