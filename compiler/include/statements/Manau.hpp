#pragma once
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
#include <string_view>

class Manau : public Statements {
public:
  static std::unique_ptr<Statements> parse_manau(Parser &parser);
  virtual void generate(CodeGenContext &) override;
  virtual bool analyze_semantics() override { return true; };

private:
  bool isConst;
  std::unique_ptr<Expression> expr;
  TypeRef data_type;
  std::string_view name;
};
