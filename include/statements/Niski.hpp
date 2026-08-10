#pragma once
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class Niski : public Statements {
public:
  Niski() : niskiCode(1) {}
  Niski(int niskicode) : niskiCode(niskicode) {}
  static std::unique_ptr<Statements> parse_niski(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  static std::unique_ptr<Statements> parse_niski_with_braces(Parser &parser);
  static std::unique_ptr<Statements> parse_niski_without_braces(Parser &parser);

private:
  int niskiCode;
};
