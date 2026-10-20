#include "IR/FunctionCall.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void FunctionCall::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("call {}\n", functionName);
}
