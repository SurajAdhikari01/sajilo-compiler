#pragma once

#include "Error.hpp"
#include "Expression/Expression.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <utility>
class ExpressionStatement : public Statements {
public:
  static std::unique_ptr<Statements>
  parse_expression_statement(Parser &parser) {
    auto expr = Expression::parse_expression(parser);
    if (!expr) {
      return nullptr;
    }
    if (parser.expect(TokenType::SEMICOLON, error::ExpectedSemicolon)) {
      return nullptr;
    }
    auto expr_statement = std::make_unique<ExpressionStatement>();
    expr_statement->expr = std::move(expr);
    return expr_statement;
  };

  void generate(CodeGenContext &) {};

private:
  std::unique_ptr<Expression> expr;
};
