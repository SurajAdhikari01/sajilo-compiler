#pragma once
#include "lexer.hpp"
#include "statements/statements.hpp"
#include "token.hpp"
#include "utils.hpp"
#include <cstddef>
#include <initializer_list>
#include <memory>
#include <string_view>
#include <utility>
#include <vector>
class Parser {
public:
  const Token &peek_token(int offset = 1) {
    return is_valid(offset) ? tokens[index + offset] : EOT;
  }
  TokenName peek_token_name() { return peek_token().token; }

  bool check(TokenName tokname) { return (current_token().token == tokname); }
  bool check_any_of(std::initializer_list<TokenName> tokens,
                    TokenName *matched_token = nullptr) {
    TokenName current = current_token().token;

    for (auto token : tokens) {
      if (token == current) {
        if (matched_token)
          *matched_token = token;
        return true;
      }
    }
    return false;
  }
  bool match(TokenName token) {
    if (token == current_token().token) {
      advance();
      return true;
    }
    return false;
  }
  bool match_any_of(std::initializer_list<TokenName> tokens,
                    TokenName *matched_token = nullptr) {

    TokenName current = current_token().token;
    for (auto token : tokens) {
      if (token == current) {
        if (matched_token)
          *matched_token = token;
        advance();
        return true;
      }
    }
    return false;
  }
  bool expect(TokenName tokenName, std::string_view error_msg) {
    if (tokenName == current_token().token) {
      advance();
      return true;
    }
    print_error(*this, error_msg);
    return false;
  }
  bool expect_any_of(std::initializer_list<TokenName> tokname,
                     std::string_view error_msg,
                     TokenName *matched_token = nullptr) {

    TokenName current = current_token().token;
    for (auto token : tokname) {
      if (token == current) {
        if (matched_token)
          *matched_token = token;
        advance();
        return true;
      }
    }
    print_error(*this, error_msg);
    return false;
  }

  const Token &current_token() const { return tokens[index]; }
  void advance() { ++index; };

  bool is_valid() { return index < tokens.size(); }
  bool is_valid(size_t i) { return i < tokens.size(); }
  void set_tokens(std::vector<Token> &tokens) {
    this->tokens = std::move(tokens);
  }
  std::unique_ptr<Statements> parse_statement();
  void parse();
  bool add_statement(std::unique_ptr<Statements> statement) {

    if (statement) {
      statements.push_back(std::move(statement));
      return true;
    }
    return false;
  }
  size_t get_current_position() { return index; }
  Token get_token(size_t i) { return is_valid(i) ? tokens[i] : EOT; }
  void set_lexer(Lexer &lexer);
  const Lexer &get_lexer() const;

private:
  std::vector<Token> tokens;
  size_t index;
  std::vector<std::unique_ptr<Statements>> statements;
  Token EOT = {TokenName::NONE};
  Lexer *lexer = nullptr;
};
