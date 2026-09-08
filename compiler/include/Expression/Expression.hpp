#pragma once
#include "parser.hpp"
#include <cstddef>
#include <memory>
class Expression {
public:
  Expression() {}
  static std::unique_ptr<Expression> parse_expression(Parser &parser);

private:
};
