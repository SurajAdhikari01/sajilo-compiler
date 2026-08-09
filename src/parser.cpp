#include "parser.hpp"
#include "statements/Exit.hpp"
#include "token.hpp"
#include <fstream>
#include <sstream>

void Parser::parse() {
  for (; index < tokens.size(); ++index) {
    scan_token(tokens[index].token);
  }
  std::stringstream ss;
  ss << "section .text\n";
  ss << "global _start\n";
  ss << "_start:\n";
  for (const auto &ptr : statements) {
    ptr->generate(ss);
  }
  std::ofstream file("out.asm");
  if (file.is_open()) {
    file << ss.str();
  }
  file.close();
}

bool Parser::scan_token(TokenName tokname) {
  switch (tokname) {
  case TokenName::NISKI: {
    auto ptr = Exit::parse_exit(*this);
    add_statement(ptr);
    return true;
  }
  default:
    return false;
  }
}
