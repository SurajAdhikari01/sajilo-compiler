#pragma once
#include "statements/statements.hpp"
class For : public Statements {
public:
  virtual bool analyze_semantics() override { return true; };

private:
};
