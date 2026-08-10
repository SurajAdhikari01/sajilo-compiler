#include "parser.hpp"
#include "statements/Bol.hpp"
#include "statements/Niski.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <fstream>
#include <iostream>
#include <sstream>

void Parser::parse() {

  for (; index < tokens.size(); ++index) {

    std::cout << tokens[index].value << std::endl;
    scan_token(tokens[index].token);
  }
  std::cout << statements.size() << std::endl;
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

  std::cout << "something something\n";

  switch (tokname) {
  case TokenName::NISKI: {
    std::cout << "something something\n";

    auto ptr = Niski::parse_niski(*this);
    if (!ptr) {
      std::cout << "something something\n";
    }
    add_statement(ptr);
    return true;
  }
  case TokenName::BOL: {
    std::cout << "something something two\n";

    auto ptr = Bol::parse_bol(*this);
    if (!ptr) {
      std::cout << "something something two\n";
    }
    add_statement(ptr);
    return true;
  }
  default:
    return false;
  }
}
