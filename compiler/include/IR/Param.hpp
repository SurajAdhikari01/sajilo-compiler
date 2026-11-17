#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Param : public IR {
public:
  Param(std::string argument, int funcIndex)
      : IR(funcIndex), argument(argument) {};

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;
  std::string argument;
};
