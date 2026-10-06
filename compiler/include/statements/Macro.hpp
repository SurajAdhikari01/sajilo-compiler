#pragma once

#include "statements/statements.hpp"
class Marco : public Statements {
public:
  virtual bool analyze_semantics(Parser &parser) override { return true; };

private:
};
