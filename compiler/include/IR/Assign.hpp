#pragma once
#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>

class Assign : public IR {
public:
  Assign(const std::string &destination_op, const std::string &source_op)
      : destination_op(destination_op), source_op(source_op) {}

  void generate_ir(CodeGenContext &, Parser &);

  std::string source_op, destination_op;
};
