#pragma once
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class While : public Statements {
public:
  virtual ~While() {};
  static std::unique_ptr<Statements> parse_while(Parser &parser);

  virtual void generate(CodeGenContext &) override {};

private:
  std::unique_ptr<Expression> condition;
  std::unique_ptr<Statements> while_block;
};
