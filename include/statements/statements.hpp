#pragma once

#include <sstream>
class Statements {
public:
  Statements() {};
  virtual ~Statements() {};
  virtual void generate(std::stringstream &ss) = 0;
};
