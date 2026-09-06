#pragma once
#include "parser.hpp"
#include <memory>
class Expression {
public:
  Expression() {}
  std::unique_ptr<Expression> parse_expression(Parser &parser);

private:
};
