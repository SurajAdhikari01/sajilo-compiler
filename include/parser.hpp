#pragma once
#include "statements/statements.hpp"
#include "token.hpp"
#include <memory>
#include <utility>
#include <vector>
class Parser {
public:
  const Token &peek_token() { return tokens[index + 1]; }
  TokenName peek_token_name() { return peek_token().token; }

  bool expect_token(TokenName tokname) {
    return (peek_token().token == tokname);
  }
  const Token &get_current_token() { return tokens[index]; }
  void consume_token() { ++index; };
  bool is_valid() { return index < tokens.size(); }
  void set_tokens(std::vector<Token> &tokens) {
    this->tokens = std::move(tokens);
  }
  bool scan_token(TokenName tokname);
  void parse();
  void add_statement(std::unique_ptr<Statements> &statement) {
    if (statement) {
      statements.push_back(std::move(statement));
    }
  }

private:
private:
  std::vector<Token> tokens;
  size_t index;
  std::vector<std::unique_ptr<Statements>> statements;
};
