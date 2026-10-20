#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Jump : public IR {
public:
  Jump(std::string destination) : destination(destination) {}

  void generate_ir(CodeGenContext &, Parser &);

  std::string destination;
};
