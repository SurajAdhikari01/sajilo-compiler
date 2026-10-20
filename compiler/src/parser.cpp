#include "parser.hpp"

#include "json.hpp"
#include "statements/Exit.hpp"
#include "statements/ExpressionStatement.hpp"
#include "statements/Function.hpp"
#include "statements/If.hpp"
#include "statements/Manau.hpp"
#include "statements/Read.hpp"
#include "statements/Return.hpp"
#include "statements/Scope.hpp"
#include "statements/While.hpp"
#include "statements/Write.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <fstream>
#include <memory>
#include <sstream>
void Parser::parse() {

  for (; index < tokens.size(); ++index) {
    if (!add_statement(parse_statement())) {
      isInvalidSyntax = true;
      break;
    }
  }
  if (!isInvalidSyntax) {
    for (const auto &ptr : statements) {
      if (!ptr->analyze_semantics(*this)) {
        isInvalidSyntax = true;
        break;
      }
    }
  }

  CodeGenContext context;
  if (!isInvalidSyntax) {

    for (const auto &ptr : statements) {
      ptr->generate_ir(context, *this);
    }
    for (const auto &instr : instructions) {
      instr->generate_ir(context, *this);
    }
  }

  std::stringstream ss;
  ss << context.code.str();
  if (!output_file.empty() && output_format != OUTPUT_FORMAT::none) {
    std::ofstream file(output_file);
    if (!file.is_open()) {
      return;
    }
    {
      std::string output_text{};
      if (output_format == OUTPUT_FORMAT::json) {

        nlohmann::json j;
        j["output"] = ss.str();

        j["error"] = err_msg;
        j["status"] = !isInvalidSyntax;
        output_text = j.dump(4);

      } else if (output_format == OUTPUT_FORMAT::text) {
        output_text = ss.str();
      }
      file << output_text;
    }
    file.close();
  }
}

std::unique_ptr<Statements> Parser::parse_statement() {
  auto tokname = current_token().token;

  switch (tokname) {
  case TokenType::JABA:
    return If::parse_if(*this);
  case TokenType::JABASAMMA:
    return While::parse_while(*this);
  case TokenType::LAIJAU: {
    return ReturnStatement::parse_return(*this);
  }
  case TokenType::EXIT: {
    return Exit::parse_exit(*this);
  }
  case TokenType::MANAU: {
    return Manau::parse_manau(*this);
  }
  case TokenType::WRITE: {
    return Write::parse_write(*this);
  }
  case TokenType::READ: {
    return Read::parse_read(*this);
  }
  case TokenType::FUNC: {
    return Function::parse_function(*this);
  }
  case TokenType::LEFT_BRACE: {
    return Scope::parse_scope(*this);
  }

  default:
    return ExpressionStatement::parse_expression_statement(*this);
  }
}

void Parser::set_lexer(Lexer &lexer) { this->lexer = &lexer; }

const Lexer &Parser::get_lexer() const { return *lexer; }
