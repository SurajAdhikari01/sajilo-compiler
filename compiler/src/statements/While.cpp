#include "statements/While.hpp"

#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "IR/CondJump.hpp"
#include "IR/Instruction.hpp"
#include "IR/Jump.hpp"
#include "statements/Scope.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <ostream>
#include <string>

std::unique_ptr<Statements> While::parse_while(Parser &parser) {
  parser.advance();
  auto while_stmt = std::make_unique<While>();
  while_stmt->location.line = parser.current_token().line_number;
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  while_stmt->condition = Expression::parse_expression(parser);
  if (!while_stmt->condition) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }

  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  while_stmt->while_block = Scope::parse_scope(parser);
  if (!while_stmt->while_block) {
    return nullptr;
  }

  return while_stmt;
}

bool While::analyze_semantics(Parser &parser) {
  if (!condition->analyze_symantics(parser, location))
    return false;
  return while_block->analyze_semantics(parser);
}

void While::generate_ir(CodeGenContext &context, Parser &parser) {

  auto cond_level = context.block_label++;
  auto then_level = context.block_label++;
  auto end_level = context.block_label++;
  auto cond = condition->generate_ir(context, parser);

  auto temp_str = 'b' + std::to_string(end_level);
  parser.add_instruction(std::make_unique<CondJump>(cond, temp_str));
  temp_str = 'b' + std::to_string(then_level);
  parser.add_instruction(std::make_unique<Label>(temp_str));

  // context.code << "b" << cond_level << ":\n";
  // context.code << "if " << cond << " jmp b" << then_level << "\njmp b"
  //              << end_level << '\n'
  //              << "b" << then_level << ":\n";

  while_block->generate_ir(context, parser);
  temp_str = 'b' + std::to_string(cond_level);
  parser.add_instruction(std::make_unique<Jump>(temp_str));

  temp_str = 'b' + std::to_string(end_level);
  parser.add_instruction(std::make_unique<Label>(temp_str));
  // context.code << "jmp b" << cond_level << '\n';
  //
  // context.code << 'b' << end_level << ":\n";
}
