#include "IR/FunctionLabel.hpp"
#include "IR/IRTable.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void FunctionLabel::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("\n{}:\n", m_funcLabel);
}

void FunctionLabel ::generate_code(CodeGenContext &context) {
  auto funcData = get_IR_Table().lookup(functionIndex);
  context.code << std::format("\n{}:\n", m_funcLabel)
               << std::format("push rbp\n") << std::format("mov rbp, rsp\n")
               << std::format("sub rsp, {}\n", funcData->framesize);
}
