#include "statements/ExpressionStatement.hpp"
#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "statements/statements.hpp"
#include <memory>
std::unique_ptr<Statements>
ExpressionStatement::parse_expression_statement(Parser &parser) {

  auto expr_statement = std::make_unique<ExpressionStatement>();
  expr_statement->location.line = parser.current_token().line_number;
  auto expr = Expression::parse_expression(parser);
  if (!expr) {
    return nullptr;
  }
  expr_statement->expr = std::move(expr);
  if (!parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
    return nullptr;
  }

  return expr_statement;
};

void ExpressionStatement::generate_ir(LabelCounters &counter, Parser &parser) {
  expr->generate_ir(counter, parser);
};
bool ExpressionStatement::analyze_semantics(Parser &parser) {
  return (expr->analyze_symantics(parser, location));
};
