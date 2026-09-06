#include "Expression/BinaryExpression.hpp"
#include "parser.hpp"
#include <memory>

std::unique_ptr<Expression> BinaryExpression::parse_expression(Parser &parser) {
  return std::make_unique<BinaryExpression>();
}
