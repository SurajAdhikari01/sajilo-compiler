#include "IR/Label.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Label::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("\n{}:\n", label);
}
