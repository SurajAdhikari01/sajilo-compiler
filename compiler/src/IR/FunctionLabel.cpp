#include "IR/FunctionLabel.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void FunctionLabel::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("\n{}:\n", m_funcLabel);
}

void FunctionLabel ::generate_code(CodeGenContext &context) {
  context.code << std::format("\n{}:\n", m_funcLabel);
}
