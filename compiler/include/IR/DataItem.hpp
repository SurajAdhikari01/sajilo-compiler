#pragma once

#include "IR/IR.hpp"
#include <string>
class Parser;
struct CodeGenContext;
class DataItem : public IR {
public:
  DataItem(const std::string &name, const std::string &value, int funcIndex)
      : IR(funcIndex), name(name), value(value) {}
  virtual void generate_ir(CodeGenContext &, Parser &) override;

  virtual void generate_code(CodeGenContext &) override;

private:
  std::string name, value;
};
