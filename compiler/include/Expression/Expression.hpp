#pragma once
#include <cstddef>
#include <memory>
class Parser;
enum class PRIMARY_TYPE
{
  INT_LITERAL,
  STRING_LITERAL,
  IDENTIFIER,
  VOID
};
class Expression
{
public:
  Expression() {}
  virtual ~Expression() = default;
  static std::unique_ptr<Expression> parse_expression(Parser &parser);
  static std::unique_ptr<Expression> pratt_expression(Parser &parser,
                                                      float min_bp);
  virtual PRIMARY_TYPE get_primary_type() { return PRIMARY_TYPE::VOID; }

private:
};
