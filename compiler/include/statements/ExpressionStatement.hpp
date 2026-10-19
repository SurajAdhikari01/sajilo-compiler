#pragma once

#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <cstddef>
#include <memory>
class ExpressionStatement : public Statements
{
public:
  static std::unique_ptr<Statements> parse_expression_statement(Parser &parser);
  virtual void generate_ir(CodeGenContext &, Parser &) override;
  virtual bool analyze_semantics(Parser &parser) override;

private:
  std::unique_ptr<Expression> expr;
};
