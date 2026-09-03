#include "parser.hpp"

#include "statements/Function.hpp"
#include "statements/Manau.hpp"
#include "statements/Niski.hpp"
#include "statements/Read.hpp"
#include "statements/Scope.hpp"
#include "statements/Write.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

void Parser::parse() {

  for (; index < tokens.size(); ++index) {

    if (!add_statement(parse_statement())) {
      std::cerr << "Syntax error\n" << current_token().value;
      return;
    }
  }
  CodeGenContext context;
  context.code << "_start:\n";
  for (const auto &ptr : statements) {
    ptr->generate(context);
  }

  std::stringstream ss;
  ss << "section .data\n"
     << context.data.str() << "\n"
     << "section .text\n"
     << "global _start\n"
     << context.code.str();

  std::ofstream file("out.asm");
  if (file.is_open()) {
    file << ss.str();
  }
  file.close();
}

std::unique_ptr<Statements> Parser::parse_statement() {
  auto tokname = current_token().token;

  switch (tokname) {
  case TokenName::NISKI: {
    return Niski::parse_niski(*this);
  }

  case TokenName::MANAU: {
    return Manau::parse_manau(*this);
  }
  case TokenName::WRITE: {
    return Write::parse_write(*this);
  }
  case TokenName::READ: {
    return Read::parse_read(*this);
  }
  case TokenName::FUNC: {
    return Function::parse_function(*this);
  }
  case TokenName::LEFT_BRACE: {
    return Scope::parse_scope(*this);
  }

  default:
    return nullptr;
  }
}

void Parser::set_lexer(Lexer &lexer) { this->lexer = &lexer; }

const Lexer &Parser::get_lexer() const { return *lexer; }
