#pragma once
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <memory>
class TernaryExpression : public Expression {
public:
  std::unique_ptr<Expression> parse_expression(Parser &parser);
  virtual PRIMITIVE_DATA_TYPES get_primitive_type() override {
    return PRIMITIVE_DATA_TYPES::VOID;
  }

private:
  enum class TN_OPERATORS { QUESTION_MARK } tn_operators;
};
