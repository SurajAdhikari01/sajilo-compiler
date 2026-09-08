#pragma once

#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class ExpressionStatement : public Statements {
public:
  static std::unique_ptr<Statements> parse_expression_statement(Parser &) {
    return nullptr;
  };

private:
  std::unique_ptr<Expression> expr;
};
