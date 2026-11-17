#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Label : public IR {
public:
  Label(std::string label, int funcIndex) : IR(funcIndex), label(label) {};

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;
  std::string label;
};
