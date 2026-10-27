#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Jump : public IR
{
public:
  Jump(std::string destination) : destination(destination) {}

  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;

  std::string destination;
};
