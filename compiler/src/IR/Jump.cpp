#include "IR/Jump.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Jump::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("jmp {}\n", destination);
}
