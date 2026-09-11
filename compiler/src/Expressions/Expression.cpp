#include "Expression/Expression.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/PrimaryExpression.hpp"
#include "Expression/UnaryExpression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <random>
#include <tuple>
#include <utility>

static std::initializer_list<TokenType> binary_tokens{
    TokenType::PLUS, TokenType::MINUS, TokenType::ASTERISK, TokenType::SLASH};

BN_OPERATORS get_binary_operator(TokenType tokenType) {
  switch (tokenType) {
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
  case BN_OPERATORS::ADDITION:
  case BN_OPERATORS::SUBTRACTION:
    return {9.0f, 9.1f};
  case BN_OPERATORS::MULTIPLICATION:
  case BN_OPERATORS::DIVISION:
  case BN_OPERATORS::MODULUS:
    return {10.0f, 10.1f};
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
