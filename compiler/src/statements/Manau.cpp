#include "statements/Manau.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "IR/Assign.hpp"
#include "parser.hpp"
#include "symbolTable.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
#include <string>

std::unique_ptr<Statements> Manau::parse_manau(Parser &parser) {
  std::unique_ptr<Manau> manau_stmt = std::make_unique<Manau>();
  manau_stmt->location.line = parser.current_token().line_number;
  parser.advance();

  if (parser.match(TokenType::COLON)) {
    if (!parser.expect(TokenType::CONST, "")) {
      return nullptr;
    }
    manau_stmt->isConst = true;
  }
  if (!parser.check_any_of({TokenType::KEYWORD, TokenType::IDENTIFIER})) {
    print_error(parser, "");
    return nullptr;
  }

  manau_stmt->data_type.name = parser.current_token().value;

  manau_stmt->data_type.data_type = get_datatypes(manau_stmt->data_type.name);
  parser.advance();

  if (!parser.check(TokenType::IDENTIFIER)) {
    return nullptr;
  }

  manau_stmt->name = parser.current_token().value;
  parser.advance();
  if (parser.match(TokenType::ASSIGN)) {
    manau_stmt->expr = Expression::parse_expression(parser);
    if (!manau_stmt->expr) {
      return nullptr;
    }
  }
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return manau_stmt;
}
void Manau::generate_ir(CodeGenContext &context, Parser &parser) {
  if (!expr)
    return;
  // name = t0
  auto exp = expr->generate_ir(context, parser);
  auto exp_str = std::string(exp);
  auto instr = std::make_unique<Assign>(std::string(name), exp_str);
  parser.add_instruction(std::move(instr));
  // context.code << name << " = " << exp << '\n';
}

bool Manau::analyze_semantics(Parser &parser) {
  decleration_data data;
  data.type = data_type;
  data.isConst = isConst;

  if (!get_table().insert(name, data)) {
    print_error(parser, error::RedefinitionOfSymbol, location);
    return false;
  }
  if (!expr) {
    return true;
  }
  if (!expr->analyze_symantics(parser, location))
    return false;
  auto type = expr->get_primitive_type();
  if (!is_compatible_datatype(data_type.data_type, type)) {
    print_error(parser, error::IncompatibleTypes, location);
    return false;
  }

  return true;
}
