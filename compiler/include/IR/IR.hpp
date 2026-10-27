#pragma once

#include <string>
class Parser;
class CodeGenContext;
class IR
{
public:
  IR() {}
  virtual ~IR() {}
  virtual void generate_ir(CodeGenContext &, Parser &) = 0;
  virtual void generate_code(CodeGenContext &) = 0;
};
