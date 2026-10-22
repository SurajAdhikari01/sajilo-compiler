#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Return : public IR {
public:
  Return(std::string argument) : argument(argument) {};
  void generate_ir(CodeGenContext &, Parser &);

  std::string argument;
};
