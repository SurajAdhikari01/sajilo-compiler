#pragma once

#include <cstdint>
#include <sstream>
struct CodeGenContext {
  std::stringstream code;
  std::stringstream data;
  uint32_t lable = 0;
};

class Statements {
public:
  Statements() {};
  virtual ~Statements() {};
  virtual void generate(CodeGenContext &) = 0;
};
