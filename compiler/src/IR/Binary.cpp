
#include "IR/binary.hpp"
#include "Expression/BinaryExpression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Binary::generate_ir(CodeGenContext &context, Parser &parser) {

  auto str = std::format("{} = {} {} {}\n", res, oprand_left,
                         get_symbol(bn_operator), oprand_right);
  context.code << str;
}
