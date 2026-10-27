#pragma once
#include "./PrimaryExpression.hpp"
#import "Expression/Expression.hpp"
#include "parser.hpp"
#include "utils.hpp"
#include <memory>
#include <string>
#include <utility>
enum class BN_OPERATORS
{
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
inline std::string get_symbol(BN_OPERATORS bn_op)
{
  switch (bn_op)
  {
  case BN_OPERATORS::NONE:
    return "";
  case BN_OPERATORS::ADDITION:
    return "+";
  case BN_OPERATORS::SUBTRACTION:
    return "-";
  case BN_OPERATORS::MULTIPLICATION:
    return "*";
  case BN_OPERATORS::DIVISION:
    return "/";
  case BN_OPERATORS::MODULUS:
    return "%";
  case BN_OPERATORS::BITWISE_XOR:
    return "^";
  case BN_OPERATORS::BITWISE_AND:
    return "&";
  case BN_OPERATORS::BITWISE_OR:
    return "|";
  case BN_OPERATORS::LESS_THAN:
    return "<";
  case BN_OPERATORS::LESS_THAN_EQUAL:
    return "<=";
  case BN_OPERATORS::GREATER_THAN:
    return ">";
  case BN_OPERATORS::GREATER_THAN_EQUAL:
    return ">=";
  case BN_OPERATORS::EQUAL_TO:
    return "==";
  case BN_OPERATORS::ASSIGN_TO:
    return "=";
  case BN_OPERATORS::NOT_EQUAL_TO:
    return "!=";
  case BN_OPERATORS::LOGICAL_AND:
    return "&&";
  case BN_OPERATORS::LOGICAL_OR:
    return "||";
  case BN_OPERATORS::LEFT_SHIFT:
    return "<<";
  case BN_OPERATORS::RIGHT_SHIFT:
    return ">>";
  case BN_OPERATORS::INDEXING:
    return "[]";
  case BN_OPERATORS::ARROW:
    return "->";
  }

  return "";
}

class BinaryExpression : public Expression
{
public:
  BinaryExpression() {};
  BinaryExpression(BN_OPERATORS bn_operators, std::unique_ptr<Expression> left,
                   std::unique_ptr<Expression> right)
      : bn_operators(bn_operators), left(std::move(left)),
        right(std::move(right)) {};
  std::unique_ptr<Expression> parse_expression(Parser &parser);
  virtual PRIMITIVE_DATA_TYPES get_primitive_type() override;
  virtual bool analyze_symantics(Parser &parser,
                                 const SourceLocation &) override;
  virtual std::string generate_ir(LabelCounters &context,
                                  Parser &parser) override;

  BN_OPERATORS bn_operators = BN_OPERATORS::NONE;
  std::unique_ptr<Expression> left;
  std::unique_ptr<Expression> right;
};
