#pragma once
#include "Expression/Expression.hpp"
#include <memory>
#include <string_view>
class Parser;

class PrimaryExpression : public Expression
{
public:
  static std::unique_ptr<Expression> parse_primary(Parser &parser);
  virtual PRIMARY_TYPE get_primary_type() override { return primary_type; }
  PRIMARY_TYPE primary_type = PRIMARY_TYPE::VOID;
  std::string_view value;
};
