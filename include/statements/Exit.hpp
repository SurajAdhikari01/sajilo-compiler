#pragma once
#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
class Exit : public Statements {
public:
  Exit() : exitCode(1) {}
  Exit(int exitcode) : exitCode(exitcode) {}
  static std::unique_ptr<Statements> parse_exit(Parser &parser);
  virtual void generate(std::stringstream &ss) override;

private:
  static std::unique_ptr<Statements> parse_exit_with_braces(Parser &parser);
  static std::unique_ptr<Statements> parse_exit_without_braces(Parser &parser);

private:
  int exitCode;
};
