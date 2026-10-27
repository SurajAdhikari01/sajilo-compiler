#include "IR/FunctionCall.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void FunctionCall::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("call {}\n", functionName);
}

void FunctionCall ::generate_code(CodeGenContext &context) {

  context.code << std::format("call {}\n", functionName);
}
