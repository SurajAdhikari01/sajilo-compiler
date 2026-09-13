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

private:
  std::unique_ptr<Expression> return_value;
};
