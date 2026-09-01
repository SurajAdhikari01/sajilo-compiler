#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
#include <vector>
class Scope : public Statements {
public:
  static std::unique_ptr<Statements> parse_scope(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::vector<std::unique_ptr<Statements>> statements;
};
