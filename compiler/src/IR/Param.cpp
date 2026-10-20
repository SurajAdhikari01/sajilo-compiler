#include "IR/Param.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Param::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("param {}\n", argument);
}
