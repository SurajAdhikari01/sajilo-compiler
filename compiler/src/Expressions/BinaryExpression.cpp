#include "Expression/BinaryExpression.hpp"
#include "Error.hpp"
#include "Expression/PrimaryExpression.hpp"
#include "IR/Assign.hpp"
#include "IR/Binary.hpp"
#include "statements/statements.hpp"
#include "utils.hpp"
#include <memory>
#include <string>
#include <utility>

std::unique_ptr<Expression> BinaryExpression::parse_expression(Parser &parser) {

  return std::make_unique<BinaryExpression>();
}

PRIMITIVE_DATA_TYPES BinaryExpression::get_primitive_type() {
  auto left_type = left->get_primitive_type();
  auto right_type = right->get_primitive_type();
  if (left_type != PRIMITIVE_DATA_TYPES::UNEXPECTED &&
      left_type == right_type) {
    return left_type;
  }
  return PRIMITIVE_DATA_TYPES::UNEXPECTED;
}

bool BinaryExpression::analyze_symantics(Parser &parser,
                                         const SourceLocation &location) {
  if (!left->analyze_symantics(parser, location))
    return false;
  if (!right->analyze_symantics(parser, location))
    return false;
  // 20 = x;
  if (bn_operators == BN_OPERATORS::ASSIGN_TO) {
    auto l = dynamic_cast<PrimaryExpression *>(left.get());
    if (!l || PRIMITIVE_DATA_TYPES::IDENTIFIER != l->primitive_data_type) {
      print_error(parser, error::InvalidAssignment, location);
      return false;
    }
  }

  auto left_type = left->get_primitive_type();
  auto right_type = right->get_primitive_type();
  if (left_type == PRIMITIVE_DATA_TYPES::UNEXPECTED ||
      right_type == PRIMITIVE_DATA_TYPES::UNEXPECTED ||
      left_type != right_type) {
    print_error(parser, error::InvalidOperandTypes, location);
    return false;
  }

  return true;
}

std::string BinaryExpression::generate_ir(CodeGenContext &context,
                                          Parser &parser) {
  auto l = left->generate_ir(context, parser);
  auto r = right->generate_ir(context, parser);

  if (bn_operators == BN_OPERATORS::ASSIGN_TO) {
    auto exp = dynamic_cast<PrimaryExpression *>(left.get());
    if (exp) {
      auto exp_val = std::string(exp->value);
      auto instr = std::make_unique<Assign>(exp_val, r);

      parser.add_instruction(std::move(instr));

      // context.code << exp->value << " = " << r << '\n';
      return exp_val;
    }
    return "";
  }

  // t0 = left operator right;
  // int x = 10;
  // x = 20;
  std::string temp = "t" + std::to_string(context.temp_label++);
  // context.code << "t" << context.temp_label << " = " << l << " "
  //              << get_symbol(bn_operators) << " " << r << '\n';
  auto instr = std::make_unique<Binary>(bn_operators, l, r, temp);

  parser.add_instruction(std::move(instr));

  return temp;
};
