#include "Expression/Expression.hpp"
#include "Expression/PrimaryExpression.hpp"
#include "Expression/UnaryExpression.hpp"
#include "parser.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Expression> Expression::parse_expression(Parser &parser) {
  auto expr = UnaryExpression::parse_prefix(parser);
  if (expr)
    return expr;

  expr = PrimaryExpression::parse_primary(parser);
  if (expr)
    return expr;

  // expr = UnaryExpression::parse_postfix(parser, expr);
  return nullptr;
}
