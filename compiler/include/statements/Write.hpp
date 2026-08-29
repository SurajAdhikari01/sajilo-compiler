#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <cstddef>
#include <memory>
#include <string_view>
class Write : public Statements {
public:
  static std::unique_ptr<Statements> parse_write(Parser &parser);

  virtual void generate(CodeGenContext &) override;

private:
  std::string_view variable;
  std::string_view length;
};
