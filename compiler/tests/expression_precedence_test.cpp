#include "Expression/BinaryExpression.hpp"
#include "Expression/Expression.hpp"
#include "Expression/PrimaryExpression.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <iostream>
#include <string>

int main() {
  std::string source = "1 + 2 * 3;";
  Lexer lexer;
  lexer.set_sourceCode(source);
  lexer.tokenize();

  Parser parser;
  parser.set_lexer(lexer);
  parser.set_tokens(lexer.get_tokens());

  auto expression = Expression::parse_expression(parser);
  const auto *addition = dynamic_cast<const BinaryExpression *>(expression.get());
  if (!addition || addition->get_operator() != BN_OPERATORS::ADDITION) {
    std::cerr << "expected addition at the root\n";
    return 1;
  }

  const auto *one = dynamic_cast<const PrimaryExpression *>(addition->get_left());
  if (!one || one->value != "1") {
    std::cerr << "expected 1 as the left operand\n";
    return 1;
  }

  const auto *multiplication =
      dynamic_cast<const BinaryExpression *>(addition->get_right());
  if (!multiplication ||
      multiplication->get_operator() != BN_OPERATORS::MULTIPLICATION) {
    std::cerr << "expected multiplication as the right operand\n";
    return 1;
  }

  const auto *two =
      dynamic_cast<const PrimaryExpression *>(multiplication->get_left());
  const auto *three =
      dynamic_cast<const PrimaryExpression *>(multiplication->get_right());
  if (!two || two->value != "2" || !three || three->value != "3") {
    std::cerr << "expected 2 and 3 as multiplication operands\n";
    return 1;
  }

  return 0;
}
