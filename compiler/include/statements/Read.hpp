#pragma once

#include "statements/statements.hpp"
#include <memory>
class Parser;
class Expression;
class Read : public Statements {
public:
  static std::unique_ptr<Statements> parse_read(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::unique_ptr<Expression> variable;
  std::unique_ptr<Expression> length;
};
