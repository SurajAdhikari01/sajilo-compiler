#pragma once

#include "parser.hpp"
#include "statements/statements.hpp"
#include "utils.hpp"
#include <memory>
#include <string_view>

struct TypeRef {
  DATA_TYPES data_type = DATA_TYPES::VOID;
  std::string_view name;
};
struct ParameterDecl {
  TypeRef type;
  std::string_view name;
};
class Function : public Statements {
public:
  static std::unique_ptr<Statements> parse_function(Parser &parser);
  virtual void generate(CodeGenContext &) override;

private:
  std::string_view func_name;
  std::vector<ParameterDecl> parameters;
  TypeRef return_type;
  std::unique_ptr<Statements> body;
  bool isDefined = false;
};
