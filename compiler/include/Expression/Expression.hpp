#pragma once
#include "parser.hpp"
#include <cstddef>
#include <memory>
class Expression {
public:
  Expression() {}
  static std::unique_ptr<Expression> parse_expression(Parser &parser);
  static std::unique_ptr<Expression> pratt_expression(Parser &parser,
                                                      float min_bp);

private:
};
