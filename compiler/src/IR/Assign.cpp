#include "IR/Assign.hpp"
#include "IR/IRTable.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>

void Assign::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("{} = {}\n", destination_op, source_op);
}
void Assign ::generate_code(CodeGenContext &context) {
  auto dest = get_IR_Table().lookup_variable(functionIndex, destination_op);
  if (!dest)
    return;
  // auto src = get_IR_Table().lookup_variable(functionIndex, source_op);
  // if (!src)
  //   return;

  const auto dest_str =
      std::format("qword [rbp - {}]", dest->offset + dest->size);
  // const auto src_str = std::format("qword [rbp - {}]", src->offset);

  context.code << std::format("mov {}, {}\n", dest_str, source_op);
}
