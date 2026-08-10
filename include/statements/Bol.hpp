#pragma once
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>

class Bol : public Statements {
public:
  Bol() : bolText("") {}
  Bol(std::string boltext) : bolText(boltext) {}
  static std::unique_ptr<Statements> parse_bol(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  static std::unique_ptr<Statements> parse_bol_string(Parser &parser);
  static std::unique_ptr<Statements> parse_bol_variable(Parser &parser);

private:
  std::string bolText;
};
