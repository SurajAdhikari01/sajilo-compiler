#pragma once

#include "token.hpp"
#include <cstddef>
#include <string>
#include <string_view>
#include <vector>

class Lexer {
public:
  void tokenize();
  std::vector<Token> &get_tokens() { return tokens; }
  void set_sourceCode(std::string &source_code);
  std::string_view get_code_line(size_t line_no) const {

    size_t start = line_start_index[line_no - 1];
    size_t end = line_no < line_start_index.size()
                     ? line_start_index[line_no] - 1
                     : source_code.size();
    if (source_code[end] == '\n' && end > start) {

      --end;
    }
    return source_code.substr(start, end - start + 1);
  }

private:
  char peek() const { return isValid() ? source_code[index + 1] : '\0'; };
  void consume() {
    current_column++;
    ++index;
  }
  bool isValid() const { return index < source_code.size(); }
  bool scan_character(const char c);
  void process_keyword(const char c);
  void add_token(Token &&token) {
    token.line_number = line_number;
    token.current_column = current_column;
    tokens.push_back(std::move(token));
  }

  void add_token(Token &token) {
    token.line_number = line_number;
    token.current_column = current_column;

    tokens.push_back(token);
  }
  const char *get_current_ptr() const { return source_code.data() + index; };
  void process_string_literal();
  void process_new_line() {
    line_number++;
    current_column = 0;
    line_start_index.push_back(index + 1);
  };

private:
  std::string_view source_code;
  size_t index = 0;
  std::vector<Token> tokens;
  int line_number = 1;
  int current_column = 0;
  std::vector<size_t> line_start_index;
  std::string_view buffer;
  size_t buffer_size = 1;
};
