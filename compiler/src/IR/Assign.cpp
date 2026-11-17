#include "IR/Assign.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>

void Assign::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("{} = {}\n", destination_op, source_op);
}
void Assign ::generate_code(CodeGenContext &context) {
  context.code << std::format("mov {}, {}\n", destination_op, source_op);
}
