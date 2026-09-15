#pragma once
#include "Expression/PrimaryExpression.hpp"
#include "statements/statements.hpp"
#include <cstddef>
#include <memory>
class Parser;
class Exit : public Statements {
public:
  static std::unique_ptr<Statements> parse_exit(Parser &parser);
  virtual void generate(CodeGenContext &) override;
  virtual bool analyze_semantics() override;

private:
  std::unique_ptr<Expression> exit_expr;
};
