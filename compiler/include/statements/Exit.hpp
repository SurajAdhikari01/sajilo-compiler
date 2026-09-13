#pragma once

#include "statements/statements.hpp"
#include <memory>
class Expression;
class Parser;
class Exit : public Statements {
public:
  static std::unique_ptr<Statements> parse_exit(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::unique_ptr<Expression> exit_expr;
};
