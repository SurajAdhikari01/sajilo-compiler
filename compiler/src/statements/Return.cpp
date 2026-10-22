#import "statements/Return.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "IR/Instruction.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>

std::unique_ptr<Statements> ReturnStatement::parse_return(Parser &parser) {
  parser.advance();

  auto return_stmt = std::make_unique<ReturnStatement>();
  return_stmt->location.line = parser.current_token().line_number;
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  return_stmt->return_expr = Expression::parse_expression(parser);

  if (!return_stmt->return_expr) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return return_stmt;
}

void ReturnStatement::generate_ir(CodeGenContext &context, Parser &parser) {

  auto exp = return_expr->generate_ir(context, parser);
  if (auto binaryExpr = dynamic_cast<BinaryExpression *>(return_expr.get());
      binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
    exp = binaryExpr->left->generate_ir(context, parser);
  }

  // context.code << "param " << exp << '\n'
  //              << "return()\n";
  //
  parser.add_instruction(std::make_unique<Return>(exp));
};
bool ReturnStatement::analyze_semantics(Parser &parser) {
  if (!return_expr->analyze_symantics(parser, location))
    return false;
  auto type = return_expr->get_primitive_type();

  if (!is_compatible_datatype(PRIMITIVE_DATA_TYPES::INT, type)) {
    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }
  return true;
};
