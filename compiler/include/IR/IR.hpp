#pragma once

class Parser;
class CodeGenContext;
class IR {
public:
  IR() {}
  virtual ~IR() {}
  virtual void generate_ir(CodeGenContext &, Parser &) = 0;
};
