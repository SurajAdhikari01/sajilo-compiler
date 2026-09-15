#pragma once

#include "statements/statements.hpp"
#include <memory>
class Expression;
class Parser;
class Return : public Statements {
public:
  Return() {}
  static std::unique_ptr<Statements> parse_return(Parser &parser);
  virtual void generate(CodeGenContext &) override;
  virtual bool analyze_semantics() override { return true; };

private:
  std::unique_ptr<Expression> return_value;
};
