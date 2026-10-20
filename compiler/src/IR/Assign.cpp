#include "IR/Assign.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"

void Assign::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("{} = {}\n", destination_op, source_op);
}
