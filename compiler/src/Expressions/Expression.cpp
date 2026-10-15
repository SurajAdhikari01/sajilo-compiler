#include "Expression/Expression.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/PrimaryExpression.hpp"
#include "Expression/UnaryExpression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <ostream>
#include <random>
#include <tuple>
#include <utility>

static std::initializer_list<TokenType> binary_tokens{
    TokenType::ASSIGN,        TokenType::OR,
    TokenType::AND,           TokenType::BIT_OR,
    TokenType::BIT_AND,       TokenType::BIT_XOR,
    TokenType::EQUAL_EQUAL,   TokenType::NOT_EQUAL,
    TokenType::LESS,          TokenType::GREATER,
    TokenType::GREATER_EQUAL, TokenType::LESS_EQUAL,
    TokenType::LEFT_SHIFT,    TokenType::RIGHT_SHIFT,
    TokenType::PLUS,          TokenType::MINUS,
    TokenType::ASTERISK,      TokenType::SLASH};

BN_OPERATORS get_binary_operator(TokenType tokenType) {
  switch (tokenType) {
  case TokenType::ASSIGN:
    return BN_OPERATORS::ASSIGN_TO;
  case TokenType::OR:
    return BN_OPERATORS::LOGICAL_OR;
  case TokenType::AND:
    return BN_OPERATORS::LOGICAL_AND;
  case TokenType::BIT_OR:
    return BN_OPERATORS::BITWISE_OR;
  case TokenType::BIT_AND:
    return BN_OPERATORS::BITWISE_AND;
  case TokenType::BIT_XOR:
    return BN_OPERATORS::BITWISE_XOR;
  case TokenType::EQUAL_EQUAL:
    return BN_OPERATORS::EQUAL_TO;
  case TokenType::NOT_EQUAL:
    return BN_OPERATORS::NOT_EQUAL_TO;
  case TokenType::LESS:
    return BN_OPERATORS::LESS_THAN;
  case TokenType::LESS_EQUAL:
    return BN_OPERATORS::LESS_THAN_EQUAL;
  case TokenType::GREATER:
    return BN_OPERATORS::GREATER_THAN;
  case TokenType::GREATER_EQUAL:
    return BN_OPERATORS::GREATER_THAN_EQUAL;
  case TokenType::LEFT_SHIFT:
    return BN_OPERATORS::LEFT_SHIFT;
  case TokenType::RIGHT_SHIFT:
    return BN_OPERATORS::RIGHT_SHIFT;
  case TokenType::PLUS:
    return BN_OPERATORS::ADDITION;
  case TokenType::MINUS:
    return BN_OPERATORS::SUBTRACTION;
  case TokenType::ASTERISK:
    return BN_OPERATORS::MULTIPLICATION;
  case TokenType::SLASH:
    return BN_OPERATORS::DIVISION;
  case TokenType::MODULO:
    return BN_OPERATORS::MODULUS;
  default:
    return BN_OPERATORS::NONE;
  }
}
std::tuple<float, float> get_binding_power(BN_OPERATORS bn_operator) {
  switch (bn_operator) {
  case BN_OPERATORS::ASSIGN_TO:
    return {1.1f, 1.0f};
  case BN_OPERATORS::LOGICAL_OR:
    return {2.0f, 2.1f};
  case BN_OPERATORS::LOGICAL_AND:
    return {3.0f, 3.1f};
  case BN_OPERATORS::BITWISE_OR:
    return {4.0f, 4.1f};
  case BN_OPERATORS::BITWISE_XOR:
    return {5.0f, 5.1f};
  case BN_OPERATORS::BITWISE_AND:
    return {6.0f, 6.1f};
  case BN_OPERATORS::EQUAL_TO:
  case BN_OPERATORS::NOT_EQUAL_TO:
    return {7.0f, 7.1f};
  case BN_OPERATORS::LESS_THAN:
  case BN_OPERATORS::GREATER_THAN:
  case BN_OPERATORS::LESS_THAN_EQUAL:
  case BN_OPERATORS::GREATER_THAN_EQUAL:
    return {8.0f, 8.1f};
  case BN_OPERATORS::LEFT_SHIFT:
  case BN_OPERATORS::RIGHT_SHIFT:
    return {9.0f, 9.1f};
  case BN_OPERATORS::ADDITION:
  case BN_OPERATORS::SUBTRACTION:
    return {10.0f, 10.1f};
  case BN_OPERATORS::MULTIPLICATION:
  case BN_OPERATORS::DIVISION:
  case BN_OPERATORS::MODULUS:
    return {11.0f, 11.1f};
  default:
    return {0.0f, 0.0f};
  }
}

std::unique_ptr<Expression> Expression::parse_expression(Parser &parser) {
  return pratt_expression(parser, 0.0f);
  // expr = UnaryExpression::parse_postfix(parser, expr);
}

std::unique_ptr<Expression> Expression::pratt_expression(Parser &parser,
                                                         float min_bp) {
  TokenType temp_token;
  std::unique_ptr<Expression> left;
  if (parser.match(TokenType::LEFT_PAREN)) {
    left = pratt_expression(parser, 0.0f);
    if (!left) {
      return nullptr;
    }
    if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
      return nullptr;
    }
  } else {

    left = UnaryExpression::parse_prefix(parser);
    if (!left) {
      return nullptr;
    }
  }

  while (true) {
    if (!parser.check_any_of(binary_tokens, &temp_token)) {
      break;
    }
    auto binary_operator = get_binary_operator(temp_token);
    auto [l_bp, r_bp] = get_binding_power(binary_operator);
    if (l_bp < min_bp) {
      break;
    }
    parser.advance();
    auto right = pratt_expression(parser, r_bp);
    if (!right) {
      return nullptr;
    }
    left = std::make_unique<BinaryExpression>(binary_operator, std::move(left),
                                              std::move(right));
  }
  return left;
}
