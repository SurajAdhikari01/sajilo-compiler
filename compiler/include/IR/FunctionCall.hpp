#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class FunctionCall : public IR {
public:
  FunctionCall(std::string functionName) : functionName(functionName) {}

  void generate_ir(CodeGenContext &, Parser &);

  std::string functionName;
};
