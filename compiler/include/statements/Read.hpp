#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
#include <string_view>
class Read : public Statements {
public:
  static std::unique_ptr<Statements> parse_read(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::string_view variable;
  std::string_view length;
};
