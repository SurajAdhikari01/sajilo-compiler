#pragma once

class Parser;
class CodeGenContext;
class IR {
public:
  IR() {}
  IR(int functionIndex) : functionIndex(functionIndex) {}
  virtual ~IR() {}
  virtual void generate_ir(CodeGenContext &, Parser &) = 0;
  virtual void generate_code(CodeGenContext &) = 0;

protected:
  int functionIndex = -1;
};
