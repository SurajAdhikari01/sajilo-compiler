#include "statements/Read.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "IR/FunctionCall.hpp"
#include "parser.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>

#include "IR/Instruction.hpp"
#include <memory>
std::unique_ptr<Statements> Read::parse_read(Parser &parser) {
  auto read_stmt = std::make_unique<Read>();
  read_stmt->location.line = parser.current_token().line_number;
  parser.advance();

  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  read_stmt->variable = Expression::parse_expression(parser);
  if (!read_stmt->variable) {
    return nullptr;
  }

  if (!parser.expect(TokenType::COMMA, error::ExpectedComma)) {
    return nullptr;
  }
  read_stmt->length = Expression::parse_expression(parser);
  if (!read_stmt->length) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }
  return read_stmt;
}
void Read::generate_ir(LabelCounters &counter, Parser &parser) {
  {
    auto exp = variable->generate_ir(counter, parser);
    if (auto binaryExpr = dynamic_cast<BinaryExpression *>(variable.get());
        binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
      exp = binaryExpr->left->generate_ir(counter, parser);
    }
    parser.add_instruction(std::make_unique<Param>(exp));

    // counter.code << "param " << exp << '\n';
  }
  {
    auto exp = length->generate_ir(counter, parser);
    if (auto binaryExpr = dynamic_cast<BinaryExpression *>(length.get());
        binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
      exp = binaryExpr->left->generate_ir(counter, parser);
    }

    parser.add_instruction(std::make_unique<Param>(exp));

    // counter.code << "param " << exp << '\n';
  }
  parser.add_instruction(std::make_unique<FunctionCall>("__sys_read"));

  // counter.code << "sys_read()\n";
}
bool Read::analyze_semantics(Parser &parser) {
  if (!variable->analyze_symantics(parser, location))
    return false;

  auto type = variable->get_primitive_type();
  if (!is_compatible_datatype(PRIMITIVE_DATA_TYPES::STRING, type)) {
    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }

  if (!length->analyze_symantics(parser, location))
    return false;

  type = length->get_primitive_type();
  if (!is_compatible_datatype(PRIMITIVE_DATA_TYPES::INT, type)) {
    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }

  return true;
}
