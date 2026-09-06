#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
#include <string_view>
class Return : public Statements {
public:
  Return() {}
  static std::unique_ptr<Statements> parse_return(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::string_view return_value;
};
