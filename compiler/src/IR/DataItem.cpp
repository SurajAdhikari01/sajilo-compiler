#include "IR/DataItem.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <format>
void DataItem::generate_ir(CodeGenContext &context, Parser &parser) {

  context.code << std::format("{}: \"{}\"\n", name, value);
}
