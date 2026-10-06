#pragma once

#include <cstdint>
#include <sstream>
class Parser;
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
  virtual bool analyze_semantics(Parser &parser) = 0;
};
