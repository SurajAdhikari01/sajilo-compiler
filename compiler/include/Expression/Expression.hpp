#pragma once
#include "utils.hpp"
#include <cstddef>
#include <memory>
class Parser;
class Expression {
public:
  Expression() {}
  virtual ~Expression() = default;
  static std::unique_ptr<Expression> parse_expression(Parser &parser);
  static std::unique_ptr<Expression> pratt_expression(Parser &parser,
                                                      float min_bp);
  virtual PRIMITIVE_DATA_TYPES get_primitive_type() {
    return PRIMITIVE_DATA_TYPES::VOID;
  }

private:
};
