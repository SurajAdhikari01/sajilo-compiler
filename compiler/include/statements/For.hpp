#pragma once
#include "parser.hpp"
#include "statements/statements.hpp"
class For : public Statements {
public:
  virtual bool analyze_semantics(Parser &parser) override { return true; };

private:
};
