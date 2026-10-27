#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class CondJump : public IR
{
public:
  CondJump(std::string cond, std::string dest) : cond(cond), dest(dest) {}

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;

  std::string cond, dest;
};
