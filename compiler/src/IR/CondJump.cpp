#include "IR/CondJump.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void CondJump::generate_ir(CodeGenContext &context, Parser &parser) {

  context.code << std::format("if false {} jmp {}\n", cond, dest);
}
void CondJump ::generate_code(CodeGenContext &context) {}
