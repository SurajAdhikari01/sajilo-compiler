#pragma once
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <memory>
#include <utility>
enum class BN_OPERATORS {
  NONE,
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
class BinaryExpression : public Expression {
public:
  BinaryExpression() {};
  BinaryExpression(BN_OPERATORS bn_operators, std::unique_ptr<Expression> left,
                   std::unique_ptr<Expression> right)
      : bn_operators(bn_operators), left(std::move(left)),
        right(std::move(right)) {};
  std::unique_ptr<Expression> parse_expression(Parser &parser);
  virtual PRIMITIVE_DATA_TYPES get_primitive_type() override {
    return PRIMITIVE_DATA_TYPES::VOID;
  }

private:
  BN_OPERATORS bn_operators = BN_OPERATORS::NONE;
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;
};
