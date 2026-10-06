#pragma once
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include <memory>
class TernaryExpression : public Expression
{
public:
  std::unique_ptr<Expression> parse_expression(Parser &parser);
  virtual PRIMARY_TYPE get_primary_type() override { return PRIMARY_TYPE::VOID; }

private:
  enum class TN_OPERATORS
  {
    QUESTION_MARK
  } tn_operators;
};
