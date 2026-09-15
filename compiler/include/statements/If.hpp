#pragma once

#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class If : public Statements {

public:
  virtual ~If() {};

  static std::unique_ptr<Statements> parse_if(Parser &parser);

  virtual void generate(CodeGenContext &) override {};
  virtual bool analyze_semantics() override { return true; };

private:
  std::unique_ptr<Expression> condition;
  std::unique_ptr<Statements> if_block;
  std::unique_ptr<Statements> else_block;
};
