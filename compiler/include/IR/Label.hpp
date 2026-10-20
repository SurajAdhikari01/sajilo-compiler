#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Label : public IR {
public:
  Label(std::string label) : label(label) {};

  void generate_ir(CodeGenContext &, Parser &);

  std::string label;
};
