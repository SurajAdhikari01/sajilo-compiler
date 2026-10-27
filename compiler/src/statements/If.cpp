#include "statements/If.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "IR/Instruction.hpp"
#include "IR/Jump.hpp"
#include "IR/Label.hpp"
#include "parser.hpp"
#include "statements/Scope.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <string>

std::unique_ptr<Statements> If::parse_if(Parser &parser) {
  parser.advance();
  auto if_stmt = std::make_unique<If>();
  if_stmt->location.line = parser.current_token().line_number;
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  if_stmt->condition = Expression::parse_expression(parser);
  if (!if_stmt->condition) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }

  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  if_stmt->if_block = Scope::parse_scope(parser);
  if (!if_stmt->if_block) {
    return nullptr;
  }

  if (!parser.match(TokenType::NATRA)) {
    return if_stmt;
  }
  if (!parser.check(TokenType::LEFT_BRACE)) {
    return nullptr;
  }

  if_stmt->else_block = Scope::parse_scope(parser);
  if (!if_stmt->else_block) {
    return nullptr;
  }

  return if_stmt;
}

bool If::analyze_semantics(Parser &parser) {
  if (!condition->analyze_symantics(parser, location))
    return false;
  auto if_val = if_block->analyze_semantics(parser);
  if (!else_block)
    return if_val;
  return if_val && else_block->analyze_semantics(parser);
}

void If::generate_ir(LabelCounters &counter, Parser &parser) {

  auto cond = condition->generate_ir(counter, parser);
  auto then_level = counter.block_label++;
  auto else_level = else_block ? counter.block_label++ : 0;
  auto end_level = counter.block_label++;
  auto false_cond = else_block ? else_level : end_level;

  auto temp_str = 'b' + std::to_string(false_cond);
  parser.add_instruction(std::make_unique<CondJump>(cond, temp_str));
  temp_str = 'b' + std::to_string(then_level);
  parser.add_instruction(std::make_unique<Label>(temp_str));

  if_block->generate_ir(counter, parser);
  // counter.code << "jmp b" << end_level << '\n';
  temp_str = 'b' + std::to_string(end_level);
  parser.add_instruction(std::make_unique<Jump>(temp_str));

  if (else_block) {
    temp_str = 'b' + std::to_string(else_level);
    parser.add_instruction(std::make_unique<Label>(temp_str));

    else_block->generate_ir(counter, parser);
    temp_str = 'b' + std::to_string(end_level);
    parser.add_instruction(std::make_unique<Jump>(temp_str));
  }
  temp_str = 'b' + std::to_string(end_level);
  parser.add_instruction(std::make_unique<Label>(temp_str));

  // counter.code << 'b' << end_level << ":\n";
}
