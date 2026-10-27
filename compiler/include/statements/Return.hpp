#pragma once

#include "statements/statements.hpp"
#include <memory>
class Expression;
class Parser;
class ReturnStatement : public Statements
{
public:
  ReturnStatement() {}
  static std::unique_ptr<Statements> parse_return(Parser &parser);
  virtual void generate_ir(LabelCounters &, Parser &) override;

  virtual bool analyze_semantics(Parser &parser) override;

private:
  std::unique_ptr<Expression> return_expr;
};
