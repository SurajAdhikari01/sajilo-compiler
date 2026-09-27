#include "lexer.hpp"
#include "parser.hpp"
#include "token.hpp"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>

static std::vector<std::string_view> split_lines(const std::string &source) {
  std::vector<std::string_view> lines;
  size_t start = 0;
  for (size_t i = 0; i < source.size(); ++i) {
    if (source[i] == '\n') {
      size_t end = i;
      if (end > start && source[end - 1] == '\r') {
        --end;
      }
      lines.emplace_back(source.data() + start, end - start);
      start = i + 1;
    }
  }
  size_t end = source.size();
  if (end > start && source[end - 1] == '\r') {
    --end;
  }
  lines.emplace_back(source.data() + start, end - start);
  return lines;
}

static bool check_source(const std::string &source) {
  std::string input = source;
  Lexer lexer;
  lexer.set_sourceCode(input);
  lexer.tokenize();

  const auto expected_lines = split_lines(input);
  if (!lexer.get_code_line(0).empty() ||
      !lexer.get_code_line(expected_lines.size() + 1).empty()) {
    return false;
  }
  for (size_t line = 1; line <= expected_lines.size(); ++line) {
    if (lexer.get_code_line(line) != expected_lines[line - 1]) {
      return false;
    }
  }
  for (const auto &token : lexer.get_tokens()) {
    if (token.line_number < 1 ||
        static_cast<size_t>(token.line_number) > expected_lines.size()) {
      return false;
    }
  }
  return true;
}

int main() {
  constexpr char alphabet[] = {'a', '0', '\n', '\r', '"', '#'};
  if (!check_source("")) {
    std::cerr << "lexer boundary property failed for empty input\n";
    return 1;
  }
  size_t cases = 1;
  for (size_t length = 1; length <= 4; ++length) {
    cases *= sizeof(alphabet);
    for (size_t encoded = 0; encoded < cases; ++encoded) {
      size_t value = encoded;
      std::string source(length, alphabet[0]);
      for (char &character : source) {
        character = alphabet[value % sizeof(alphabet)];
        value /= sizeof(alphabet);
      }
      if (!check_source(source)) {
        std::cerr << "lexer boundary property failed for length " << length
                  << ", case " << encoded << '\n';
        return 1;
      }
    }
  }

  std::vector<Token> tokens{{TokenType::INT_LITERAL, "1"}};
  Parser parser;
  parser.set_tokens(tokens);
  if (parser.current_token().token != TokenType::INT_LITERAL ||
      parser.peek_token(0).token != TokenType::INT_LITERAL ||
      parser.peek_token().token != TokenType::NONE) {
    std::cerr << "parser lookahead boundary failed\n";
    return 1;
  }
  parser.advance();
  if (parser.current_token().token != TokenType::NONE ||
      parser.peek_token().token != TokenType::NONE) {
    std::cerr << "parser end-of-input boundary failed\n";
    return 1;
  }

  return 0;
}
