#pragma once

#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
class Return : public IR {
public:
  void generate_ir(CodeGenContext &, Parser &);
};
