#pragma once

#include "utils.hpp"
#include <cstdint>
#include <sstream>
class Parser;
struct CodeGenContext {
  std::stringstream code;
  std::stringstream data;
  std::stringstream rodata;
  std::stringstream bss;
  std::stringstream syscall;
};

struct LabelCounters {
  uint32_t label = 0;
  uint32_t temp_label = 0;
  uint32_t block_label = 0;
  uint32_t string_label = 0;
};

class Statements {
public:
  Statements() {};
  virtual ~Statements() {};
  virtual void generate_ir(LabelCounters &, Parser &) = 0;
  virtual bool analyze_semantics(Parser &parser) = 0;

protected:
  SourceLocation location;
};
