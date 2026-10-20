#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Param : public IR {
public:
  Param(std::string argument) : argument(argument) {};

  void generate_ir(CodeGenContext &, Parser &);

  std::string argument;
};
