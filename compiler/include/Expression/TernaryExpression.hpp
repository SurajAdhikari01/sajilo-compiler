#pragma once
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include <memory>
class TernaryExpression : public Expression {
public:
  TernaryExpression();
  std::unique_ptr<Expression> parse_expression(Parser &parser);

private:
  enum class TN_OPERATORS { QUESTION_MARK } tn_operators;
};
