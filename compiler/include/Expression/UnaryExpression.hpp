#pragma once
#import "Expression/Expression.hpp"
#include <memory>
class UnaryExpression : public Expression {
public:
  static std::unique_ptr<Expression> parse_prefix(Parser &parser);
  static std::unique_ptr<Expression>
  parse_postfix(Parser &parser, std::unique_ptr<Expression> operand);
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
    NONE,
  };

private:
  UN_OPERATORS un_operator = UN_OPERATORS::NONE;
  std::unique_ptr<Expression> un_operand;
};
