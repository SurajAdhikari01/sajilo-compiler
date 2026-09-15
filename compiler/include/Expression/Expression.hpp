#pragma once
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

private:
};
