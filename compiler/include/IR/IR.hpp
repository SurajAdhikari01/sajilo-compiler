#pragma once

#include "statements/statements.hpp"
class IR {
public:
  IR() {}
  virtual ~IR() {}
  virtual void generate_ir(CodeGenContext &, Parser &) = 0;
};
