#include "IR/Jump.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void Jump::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("jmp {}\n", destination);
}

void Jump ::generate_code(CodeGenContext &context) {
  context.code << std::format("jmp {}\n", destination);
}
