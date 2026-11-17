#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class FunctionCall : public IR {
public:
  FunctionCall(std::string functionName, int funcIndex)
      : IR(funcIndex), functionName(functionName) {}

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;
  std::string functionName;
};
