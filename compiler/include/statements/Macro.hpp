#pragma once

#include "statements/statements.hpp"
class Marco : public Statements {
public:
  virtual bool analyze_semantics() override { return true; };

private:
};
