#include "Expression/TernaryExpression.hpp"
#include "parser.hpp"
#include <memory>

std::unique_ptr<Expression>
TernaryExpression::parse_expression(Parser &parser) {
  return std::make_unique<TernaryExpression>();
}
