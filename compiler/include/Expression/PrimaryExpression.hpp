#pragma once
#include "Expression/Expression.hpp"
#include <memory>
#include <string_view>
class Parser;

class PrimaryExpression : public Expression {
public:
  static std::unique_ptr<Expression> parse_primary(Parser &parser);
  virtual PRIMITIVE_DATA_TYPES get_primitive_type() override;
  virtual bool analyze_symantics(Parser &parser,
                                 const SourceLocation &) override;
  virtual std::string generate(CodeGenContext &) override {
    return std::string(value);
  }

  PRIMITIVE_DATA_TYPES primitive_data_type = PRIMITIVE_DATA_TYPES::VOID;
  std::string_view value;
};
