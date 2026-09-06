#pragma once
#import "Expression/Expression.hpp"
class UnaryExpression : public Expression {
public:
  UnaryExpression();
  std::unique_ptr<Expression> parse_expression(Parser &parser);

private:
  enum class UN_OPERATORS {
    POST_INCR,
    PRE_INCR,
    POST_DECR,
    PRE_DECR,
    DEREFERENCE,
    REFERENCE,
    LOGICAL_NOT,
    BITWISE_NOT,
    POSITIVE,
    NEGATIVE,

  };
  UN_OPERATORS un_operator{};
};
