#include "parser.hpp"
#include "IR/IR.hpp"
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
#include "utils.hpp"
#include <cstddef>
#include <fstream>
#include <memory>
#include <sstream>
void Parser::parse() {

  while (is_valid()) {
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
  LabelCounters counter;
  if (!isInvalidSyntax) {
    add_string_literal_instruction(counter, *this);
    for (const auto &ptr : statements) {
      ptr->generate_ir(counter, *this);
    }
    for (const auto &instr : instructions) {
      // instr->generate_ir(context, *this);
      instr->generate_code(context);
    }
  }

  std::stringstream ss;
  {
    ss << "section .data\n"
       << context.data.str() << "\n\n"
       << "section .text\n"
       << "global _start\n\n"
       << context.code.str();
  }
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

bool Parser::add_statement(std::unique_ptr<Statements> statement) {

  if (statement) {
    statements.push_back(std::move(statement));
    return true;
  }
  return false;
}
bool Parser::add_instruction(std::unique_ptr<IR> instr) {
  if (instr) {
    instructions.push_back(std::move(instr));
    return true;
  }
  return false;
}
