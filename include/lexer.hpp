#include "token.hpp"
#include <string>
#include <string_view>
#include <vector>

class Lexer {
public:
  void tokenize();
  const std::vector<Token> &get_tokens() const;
  void set_sourceCode(std::string &source_code);

private:
  char peek() const { return isValid() ? source_code[index + 1] : '\0'; };
  void consume() { ++index; }
  bool isValid() const { return index < source_code.size(); }
  bool scan_character(const char c);
  void process_keyword(const char c);
  void add_token(Token &&token) { tokens.push_back(std::move(token)); }

  void add_token(Token &token) { tokens.push_back(token); }
  char *get_current_ptr() { return source_code.data() + index; };
  void process_string_literal();

private:
  std::string source_code;
  size_t index = 0;
  std::vector<Token> tokens;
  std::string_view buffer;
  size_t buffer_size = 1;
};
