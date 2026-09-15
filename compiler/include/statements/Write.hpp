#pragma once

#include "statements/statements.hpp"
#include <cstddef>
#include <memory>
class Parser;
class Expression;
class Write : public Statements {
public:
  static std::unique_ptr<Statements> parse_write(Parser &parser);

  virtual void generate(CodeGenContext &) override;
  virtual bool analyze_semantics() override { return true; };

private:
  std::unique_ptr<Expression> variable;
  std::unique_ptr<Expression> length;
};
