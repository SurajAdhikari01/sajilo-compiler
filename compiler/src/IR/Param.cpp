#include "IR/Param.hpp"
#include "IR/IRTable.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
#include <string_view>
void Param::generate_ir(CodeGenContext &context, Parser &parser) {
  context.code << std::format("param {}\n", argument);
}
static const std::array<std::string_view, 6> c_register = {"rdi", "rsi", "rdx",
                                                           "rcx", "r8",  "r9"};
void Param ::generate_code(CodeGenContext &context) {

  if (context.arg_index >= c_register.size())
    return;
  auto src = get_IR_Table().lookup_variable(functionIndex, argument);
  if (!src)
    return;

  const auto src_str = std::format("qword [rbp - {}]", src->offset + src->size);

  context.code << std::format("mov {}, {}\n", c_register[context.arg_index++],
                              src_str);
}
