#pragma once
#include "parser.hpp"
#include "statements/statements.hpp"
#include <cstddef>
#include <memory>

class Manau : public Statements {
public:
  Manau() : varName("") {}
  Manau(std::string &varName) : varName(std::move(varName)) {}
  Manau(std::string &&varName) : varName(std::move(varName)) {}
  static std::unique_ptr<Statements> parse_manau(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  static std::unique_ptr<Statements> parse_string(Parser &parser, size_t);

private:
  std::string varName;
};
