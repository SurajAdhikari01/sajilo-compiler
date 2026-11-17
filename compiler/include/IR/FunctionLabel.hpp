#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class FunctionLabel : public IR {
public:
  FunctionLabel(std::string label, int funcIndex)
      : IR(funcIndex), m_funcLabel(label) {};

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;
  std::string m_funcLabel;
};
