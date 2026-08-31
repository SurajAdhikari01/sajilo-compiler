#include "parser.hpp"
#include "statements/Bol.hpp"
#include "statements/Manau.hpp"
#include "statements/Niski.hpp"
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
      std::cerr << "Syntax error\n" << index;
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
  case TokenName::BOL: {
    return Bol::parse_bol(*this);
  }
  case TokenName::MANAU: {
    return Manau::parse_manau(*this);
  }
  case TokenName::WRITE: {
    return Write::parse_write(*this);
  }

  default:
    return nullptr;
  }
}
