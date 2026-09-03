#include "statements/Scope.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
std::unique_ptr<Statements> Scope::parse_scope(Parser &parser) {
  parser.advance();
  while (!parser.match(TokenName::RIGHT_BRACE)) {
    if (!parser.parse_statement()) {
      return nullptr;
    }
  }
  return std::make_unique<Scope>();
};

void Scope::generate(CodeGenContext &) {};
