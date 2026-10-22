#include "IR/Return.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Return::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << "return " << argument << '\n';
}
