#include "IR/Label.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void Label::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("\n{}:\n", label);
}

void Label ::generate_code(CodeGenContext &context) {
  context.code << std::format("\n{}:\n", label);
}
