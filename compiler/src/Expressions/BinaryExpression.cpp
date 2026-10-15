#include "Expression/BinaryExpression.hpp"
#include "Error.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <memory>

std::unique_ptr<Expression> BinaryExpression::parse_expression(Parser &parser) {

  return std::make_unique<BinaryExpression>();
}

PRIMITIVE_DATA_TYPES BinaryExpression::get_primitive_type() {
  auto left_type = left->get_primitive_type();
  auto right_type = right->get_primitive_type();
  if (left_type != PRIMITIVE_DATA_TYPES::UNEXPECTED &&
      left_type == right_type) {
    return left_type;
  }
  return PRIMITIVE_DATA_TYPES::UNEXPECTED;
}

bool BinaryExpression::analyze_symantics(Parser &parser,
                                         const SourceLocation &location) {
  if (!left->analyze_symantics(parser, location))
    return false;
  if (!right->analyze_symantics(parser, location))
    return false;

  auto left_type = left->get_primitive_type();
  auto right_type = right->get_primitive_type();
  if (left_type == PRIMITIVE_DATA_TYPES::UNEXPECTED ||
      right_type == PRIMITIVE_DATA_TYPES::UNEXPECTED ||
      left_type != right_type) {
    print_error(parser, error::InvalidOperandTypes, location);
    return false;
  }

  return true;
}
