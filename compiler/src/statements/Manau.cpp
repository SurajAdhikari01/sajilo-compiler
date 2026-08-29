#include "statements/Manau.hpp"
#include "symbolTable.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <memory>
#include <string>

std::unique_ptr<Statements> Manau::parse_manau(Parser &parser) {
  if (!parser.expect_token(TokenName::IDENTIFIER)) {
    return nullptr;
  }
  parser.consume_token();
  auto pos = parser.get_current_position();

  if (!parser.expect_token(TokenName::COLON)) {
    return nullptr;
  }
  parser.consume_token();
  if (!parser.expect_token(TokenName::STRING)) {
    return nullptr;
  }

  return parse_string(parser, pos);
}
void Manau::generate(CodeGenContext &) {}

std::unique_ptr<Statements> Manau::parse_string(Parser &parser, size_t pos) {
  parser.consume_token();
  if (!parser.expect_token(TokenName::ASSIGN)) {
    return nullptr;
  }
  parser.consume_token();
  if (!parser.expect_token(TokenName::STRING_LITERAL)) {
    return nullptr;
  }

  parser.consume_token();
  std::string string_literal =
      string_view_to_string(parser.get_current_token().value);
  if (!parser.expect_token(TokenName::SEMICOLON)) {
    return nullptr;
  }
  parser.consume_token();
  std::string variable_name(parser.get_token(pos).value);
  decleration_data dec_data;
  dec_data.value = string_literal;
  dec_data.dataType = DataTypes::STRING;
  dec_data.isConst = false;

  get_table().insert(variable_name, dec_data);
  return std::make_unique<Manau>(variable_name);
}
