#pragma once
#include "Expression/Expression.hpp"
#include <memory>
#include <string_view>
class Parser;
class PrimaryExpression : public Expression {
public:
  static std::unique_ptr<Expression> parse_primary(Parser &parser);

  enum class PRIMARY_TYPE {
    INT_LITERAL,
    STRING_LITERAL,
    IDENTIFIER,
    VOID
  } primary_type = PRIMARY_TYPE::VOID;
  std::string_view value;
};
