#include "Expression/UnaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <initializer_list>
#include <memory>

UnaryExpression::UN_OPERATORS get_unary_operator_prefix(TokenName tokenName) {
  switch (tokenName) {
  case TokenName::AND:
    return UnaryExpression::UN_OPERATORS::REFERENCE;
  case TokenName::INCREMENT:
    return UnaryExpression::UN_OPERATORS::PRE_INCR;
  case TokenName::DECREMENT:
    return UnaryExpression::UN_OPERATORS::PRE_DECR;
  case TokenName::PLUS:
    return UnaryExpression::UN_OPERATORS::POSITIVE;
  case TokenName::MINUS:
    return UnaryExpression::UN_OPERATORS::NEGATIVE;
  case TokenName::STAR:
    return UnaryExpression::UN_OPERATORS::DEREFERENCE;
  case TokenName::NOT:
    return UnaryExpression::UN_OPERATORS::LOGICAL_NOT;
  case TokenName::BIT_NOT:
    return UnaryExpression::UN_OPERATORS::BITWISE_NOT;
  default:
    return UnaryExpression::UN_OPERATORS::NONE;
    ;
  }
}
UnaryExpression::UN_OPERATORS get_unary_operator_postfix(TokenName tokenName) {
  switch (tokenName) {
  case TokenName::INCREMENT:
    return UnaryExpression::UN_OPERATORS::POST_INCR;
  case TokenName::DECREMENT:
    return UnaryExpression::UN_OPERATORS::POST_DECR;
  default:
    return UnaryExpression::UN_OPERATORS::NONE;
  }
}

std::unique_ptr<Expression> UnaryExpression::parse_prefix(Parser &parser) {
  static const std::initializer_list<TokenName> unary_operator = {
      TokenName::INCREMENT, TokenName::DECREMENT, TokenName::BIT_NOT,
      TokenName::NOT,       TokenName::PLUS,      TokenName::MINUS,
      TokenName::STAR,      TokenName::AND,
  };
  TokenName tempToken;
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

  static const std::initializer_list<TokenName> unary_operator = {
      TokenName::INCREMENT, TokenName::DECREMENT};
  TokenName tempToken;
  if (!parser.match_any_of(unary_operator, &tempToken)) {
    return nullptr;
  }
  auto unaryExpr = std::make_unique<UnaryExpression>();
  unaryExpr->un_operator = get_unary_operator_postfix(tempToken);
  unaryExpr->un_operand = Expression::parse_expression(parser);

  return unaryExpr;
}
