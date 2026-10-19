#include "statements/Scope.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include "symbolTable.hpp"
#include "token.hpp"
#include <cstddef>
#include <memory>
#include <utility>
std::unique_ptr<Statements> Scope::parse_scope(Parser &parser)
{
  auto scope_stmt = std::make_unique<Scope>();
  parser.advance();
  while (!parser.match(TokenType::RIGHT_BRACE))
  {
    auto stmt = parser.parse_statement();
    if (!stmt)
    {
      return nullptr;
    }
    scope_stmt->statements.emplace_back(std::move(stmt));
  }
  return scope_stmt;
};

void Scope::generate_ir(CodeGenContext &context, Parser &parser)
{
  for (const auto &stmt : statements)
  {
    stmt->generate_ir(context, parser);
  }
};

bool Scope::analyze_semantics(Parser &parser)
{
  get_table().enter_scope();

  for (const auto &ptr : statements)
  {
    if (!ptr->analyze_semantics(parser))
    {
      return false;
    }
  }
  get_table().exit_scope();
  return true;
};
