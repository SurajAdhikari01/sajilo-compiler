#pragma once

#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class If : public Statements {

public:
  If();
  virtual ~If() {};

  static std::unique_ptr<Statements> parse_if(Parser &parser);

  virtual void generate(CodeGenContext &) override;

private:
  std::unique_ptr<Expression> condition;
  std::unique_ptr<Statements> if_block;
  std::unique_ptr<Statements> else_block;
};
