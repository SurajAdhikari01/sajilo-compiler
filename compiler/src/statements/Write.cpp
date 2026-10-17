#include "statements/Write.hpp"
#include "Error.hpp"
#include "Expression/BinaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Write::parse_write(Parser &parser) {
  auto write_stmt = std::make_unique<Write>();

  write_stmt->location.line = parser.current_token().line_number;
  parser.advance();
  if (!parser.expect(TokenType::LEFT_PAREN, error::ExpectedLeftParen)) {
    return nullptr;
  }
  write_stmt->variable = Expression::parse_expression(parser);

  if (!write_stmt->variable) {
    return nullptr;
  }
  if (!parser.expect(TokenType::COMMA, error::ExpectedComma)) {
    return nullptr;
  }
  write_stmt->length = Expression::parse_expression(parser);

  if (!write_stmt->length) {
    return nullptr;
  }
  if (!parser.expect(TokenType::RIGHT_PAREN, error::ExpectedRightParen)) {
    return nullptr;
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }
  return write_stmt;
}

void Write::generate(CodeGenContext &context) {
  {
    auto exp = variable->generate(context);
    if (auto binaryExpr = dynamic_cast<BinaryExpression *>(variable.get());
        binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
      exp = binaryExpr->left->generate(context);
    }

    context.code << "param " << exp << '\n';
  }
  {
    auto exp = length->generate(context);
    if (auto binaryExpr = dynamic_cast<BinaryExpression *>(length.get());
        binaryExpr && binaryExpr->bn_operators == BN_OPERATORS::ASSIGN_TO) {
      exp = binaryExpr->left->generate(context);
    }

    context.code << "param " << exp << '\n';
  }

  context.code << "sys_write()\n";
}

bool Write::analyze_semantics(Parser &parser) {
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
