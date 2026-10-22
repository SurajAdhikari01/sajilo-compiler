#pragma once

#include "IR/IR.hpp"
#include <string>
class Parser;
struct CodeGenContext;
class DataItem : public IR {
public:
  DataItem(const std::string &name, const std::string &value)
      : name(name), value(value) {}
  void generate_ir(CodeGenContext &, Parser &);

private:
  std::string name, value;
};
