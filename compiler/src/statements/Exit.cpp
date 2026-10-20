#import "statements/Exit.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "IR/FunctionCall.hpp"
#include "IR/Instruction.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Exit::parse_exit(Parser &parser) {
  parser.advance();
  auto exit_stmt = std::make_unique<Exit>();
  exit_stmt->location.line = parser.current_token().line_number;
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  exit_stmt->exit_expr = Expression::parse_expression(parser);
  if (!exit_stmt->exit_expr) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return exit_stmt;
}

void Exit::generate_ir(CodeGenContext &context, Parser &parser) {
  auto exp = exit_expr->generate_ir(context, parser);
  if (auto binaryExpr = dynamic_cast<BinaryExpression *>(exit_expr.get());
      binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
    exp = binaryExpr->left->generate_ir(context, parser);
  }
  parser.add_instruction(std::make_unique<Param>(exp));
  parser.add_instruction(std::make_unique<FunctionCall>("sys_exit"));

  // context.code << "param " << exp << '\n'
  //              << "sys_exit()\n";
}
bool Exit::analyze_semantics(Parser &parser) {
  if (!exit_expr->analyze_symantics(parser, location))
    return false;
  auto type = exit_expr->get_primitive_type();
  if (!is_compatible_datatype(PRIMITIVE_DATA_TYPES::INT, type)) {

    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }
  return true;
};
