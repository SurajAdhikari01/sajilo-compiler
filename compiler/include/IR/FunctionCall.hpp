#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class FunctionCall : public IR
{
public:
  FunctionCall(std::string functionName) : functionName(functionName) {}

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;
  std::string functionName;
};
