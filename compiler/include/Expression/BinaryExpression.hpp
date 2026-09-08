#pragma once
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include <memory>
class BinaryExpression : public Expression {
public:
  std::unique_ptr<Expression> parse_expression(Parser &parser);

private:
  enum class BN_OPERATORS {
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION,
    MODULUS,
    BITWISE_XOR,
    BITWISE_AND,
    BITWISE_OR,
    LESS_THAN,
    LESS_THAN_EQUAL,
    GREATER_THAN,
    GREATER_THAN_EQUAL,
    EQUAL_TO,
    ASSIGN_TO,
    NOT_EQUAL_TO,
    LOGICAL_AND,
    LOGICAL_OR,
    LEFT_SHIFT,
    RIGHT_SHIFT,
    INDEXING,
    ARROW
  };

  BN_OPERATORS bn_operators{};
};
