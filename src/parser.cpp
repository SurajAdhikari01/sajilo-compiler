#include "parser.hpp"
#include "statements/Bol.hpp"
#include "statements/Manau.hpp"
#include "statements/Niski.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void Parser::parse() {

  for (; index < tokens.size(); ++index) {

    if (!scan_token(tokens[index].token)) {
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

bool Parser::scan_token(TokenName tokname) {
  switch (tokname) {
  case TokenName::NISKI: {
    auto ptr = Niski::parse_niski(*this);
    add_statement(ptr);
    return true;
  }
  case TokenName::BOL: {
    auto ptr = Bol::parse_bol(*this);
    add_statement(ptr);
    return true;
  }
  case TokenName::MANAU: {
    auto ptr = Manau::parse_manau(*this);
    add_statement(ptr);
    return true;
  }

  default:
    std::cout << get_current_token().value << std::endl;
    return false;
  }
}
