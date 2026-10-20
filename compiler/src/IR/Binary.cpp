
#include "IR/Binary.hpp"
#include "Expression/BinaryExpression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
void Binary::generate_ir(CodeGenContext &context, Parser &parser) {

  context.code << std::format("{} = {} {} {}\n", res, oprand_left,
                              get_symbol(bn_operator), oprand_right);
}
