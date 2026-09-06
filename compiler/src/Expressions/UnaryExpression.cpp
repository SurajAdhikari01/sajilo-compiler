#include "Expression/UnaryExpression.hpp"
#include "parser.hpp"
#include <memory>

std::unique_ptr<Expression> UnaryExpression::parse_expression(Parser &parser) {
  return std::make_unique<UnaryExpression>();
}
