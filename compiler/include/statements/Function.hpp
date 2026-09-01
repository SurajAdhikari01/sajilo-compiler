#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include <memory>
#include <string_view>
#include <vector>

enum class DATA_TYPE {
  INT,
  CHAR,
  VOID,
  FLOAT,
  USER_DEFINED,

};

struct Parameters {
  DATA_TYPE data_type = DATA_TYPE::VOID;
  std::string_view variable_name;
};
class Function : public Statements {
public:
  static std::unique_ptr<Statements> parse_function(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::string_view func_name;
  std::vector<Parameters> parameters;
  DATA_TYPE return_type = DATA_TYPE::VOID;
  std::vector<std::unique_ptr<Statements>> body;
  bool isDefined = false;
};
