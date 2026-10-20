#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class CondJump : public IR {
public:
  CondJump(std::string cond, std::string dest) : cond(cond), dest(dest) {}

  void generate_ir(CodeGenContext &, Parser &);

  std::string cond, dest;
};
