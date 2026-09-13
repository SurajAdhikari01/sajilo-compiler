#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include "utils.hpp"
#include <memory>
#include <string_view>
#include <vector>

struct Parameters {
  DATA_TYPES data_type = DATA_TYPES::VOID;
  std::string_view variable_name;
};
class Function : public Statements {
public:
  static std::unique_ptr<Statements> parse_function(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::string_view func_name;
  std::vector<Parameters> parameters;
  Parameters return_type;
  std::unique_ptr<Statements> body;
  bool isDefined = false;
};
