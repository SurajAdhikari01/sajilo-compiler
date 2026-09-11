#include "lexer.hpp"
#include "token.hpp"
#include <string_view>

static bool isKeyword(const std::string_view value, Token &token) {
  constexpr static std::pair<std::string_view, Token> keyword_map[] = {
      {"suru", {TokenType::SURU}},     {"read", {TokenType::READ}},
      {"write", {TokenType::WRITE}},   {"jaba", {TokenType::JABA}},
      {"laijau", {TokenType::LAIJAU}}, {"natra", {TokenType::NATRA}},
      {"deu", {TokenType::DEU}},       {"int", {TokenType::KEYWORD, "int"}},
      {"niski", {TokenType::NISKI}},   {"func", {TokenType::FUNC}},
      {"manau", {TokenType::MANAU}},

  };
  for (const auto &[map_view, map_token] : keyword_map) {
    if (map_view == value) {
      token = map_token;
      return true;
    }
  }
  return false;
}

void Lexer::set_sourceCode(std::string &data) { this->source_code = data; }

void Lexer::tokenize() {
  line_start_index.push_back(0);
  for (; index < source_code.size(); index++) {
    const char c = source_code[index];
    if (!process_symbol(c)) {
      process_keyword(c);
    }
  }
}

bool Lexer::process_symbol(char c) {
  switch (c) {
  // ---------------------------------------------------------
  // Whitespace / newline
  // ---------------------------------------------------------
  case '\n':
    process_new_line();
    return true;

  case ' ':
  case '\t':
  case '\r':
    return true;

  // ---------------------------------------------------------
  // Delimiters
  // ---------------------------------------------------------
  case '(':
    add_token({TokenType::LEFT_PAREN});
    return true;

  case ')':
    add_token({TokenType::RIGHT_PAREN});
    return true;

  case '[':
    add_token({TokenType::LEFT_BRACKET});
    return true;

  case ']':
    add_token({TokenType::RIGHT_BRACKET});
    return true;

  case '{':
    add_token({TokenType::LEFT_BRACE});
    return true;

  case '}':
    add_token({TokenType::RIGHT_BRACE});
    return true;

  case ',':
    add_token({TokenType::COMMA});
    return true;

  case '.':
    add_token({TokenType::DOT});
    return true;

  case ':':
    add_token({TokenType::COLON});
    return true;

  case ';':
    add_token({TokenType::SEMICOLON});
    return true;

  case '?':
    add_token({TokenType::QUESTION});
    return true;

  // ---------------------------------------------------------
  // Arithmetic / assignment
  // ---------------------------------------------------------
  case '+':
    if (peek() == '+') {
      consume();
      add_token({TokenType::INCREMENT});
    } else if (peek() == '=') {
      consume();
      add_token({TokenType::PLUS_ASSIGN});
    } else {
      add_token({TokenType::PLUS});
    }
    return true;

  case '-':
    if (peek() == '-') {
      consume();
      add_token({TokenType::DECREMENT});
    } else if (peek() == '=') {
      consume();
      add_token({TokenType::MINUS_ASSIGN});
    } else if (peek() == '>') {
      consume();
      add_token({TokenType::ARROW});
    } else {
      add_token({TokenType::MINUS});
    }
    return true;

  case '*':
    if (peek() == '=') {
      consume();
      add_token({TokenType::ASTERISK_ASSIGN});
    } else {
      add_token({TokenType::ASTERISK});
    }
    return true;

  case '/':
    if (peek() == '=') {
      consume();
      add_token({TokenType::SLASH_ASSIGN});
    } else {
      add_token({TokenType::SLASH});
    }
    return true;

  case '%':
    if (peek() == '=') {
      consume();
      add_token({TokenType::MODULO_ASSIGN});
    } else {
      add_token({TokenType::MODULO});
    }
    return true;

  // ---------------------------------------------------------
  // Assignment / equality
  // ---------------------------------------------------------
  case '=':
    if (peek() == '=') {
      consume();
      add_token({TokenType::EQUAL_EQUAL});
    } else {
      add_token({TokenType::ASSIGN});
    }
    return true;

  // ---------------------------------------------------------
  // Logical NOT / inequality
  // ---------------------------------------------------------
  case '!':
    if (peek() == '=') {
      consume();
      add_token({TokenType::NOT_EQUAL});
    } else {
      add_token({TokenType::NOT});
    }
    return true;

  // ---------------------------------------------------------
  // Comparison / shifts
  // ---------------------------------------------------------
  case '<':
    if (peek() == '=') {
      consume();
      add_token({TokenType::LESS_EQUAL});
    } else if (peek() == '<') {
      consume();
      add_token({TokenType::LEFT_SHIFT});
    } else {
      add_token({TokenType::LESS});
    }
    return true;

  case '>':
    if (peek() == '=') {
      consume();
      add_token({TokenType::GREATER_EQUAL});
    } else if (peek() == '>') {
      consume();
      add_token({TokenType::RIGHT_SHIFT});
    } else {
      add_token({TokenType::GREATER});
    }
    return true;

  // ---------------------------------------------------------
  // Logical / bitwise
  // ---------------------------------------------------------
  case '&':
    if (peek() == '&') {
      consume();
      add_token({TokenType::AND});
    } else {
      add_token({TokenType::BIT_AND});
    }
    return true;

  case '|':
    if (peek() == '|') {
      consume();
      add_token({TokenType::OR});
    } else {
      add_token({TokenType::BIT_OR});
    }
    return true;

  case '^':
    add_token({TokenType::BIT_XOR});
    return true;

  case '~':
    add_token({TokenType::BIT_NOT});
    return true;

  // ---------------------------------------------------------
  // Comments
  //
  // # this is a comment
  // ---------------------------------------------------------
  case '#':
    while (isValid() && peek() != '\n') {
      consume();
    }

    // Don't consume '\n' here.
    // Let the main lexer loop process it normally.
    return true;

  // ---------------------------------------------------------
  // Literals
  // ---------------------------------------------------------
  case '"':
    process_string_literal();
    return true;

  case '\'':
    // process_char_literal();
    return true;

  default:
    return false;
  }
}

void Lexer::process_keyword(char c) {
  auto isNum = [](char c) -> bool { return ('0' <= c && c <= '9'); };

  auto isChar = [](char c) -> bool {
    return ('A' <= c && c <= 'Z' || 'a' <= c && c <= 'z' || '_' == c);
  };
  const char *first_ptr = get_current_ptr();
  if (isChar(c)) {
    while (isChar(peek()) || isNum(peek())) {
      consume();
    }
    buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
    if (Token token; isKeyword(buffer, token)) {
      add_token(token);
    } else {
      add_token({TokenType::IDENTIFIER, buffer});
    }
  }
  if (isNum(c)) {
    first_ptr = get_current_ptr();

    while (isNum(peek())) {
      consume();
    }
    buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
    add_token({TokenType::INT_LITERAL, buffer});
  }
};

void Lexer::process_string_literal() {
  if (peek() == '"') {
    add_token({TokenType::STRING_LITERAL});
    consume();
    return;
  }

  consume();
  const char *first_ptr = get_current_ptr();
  while (peek() != '"' && peek() != '\0') {
    consume();
  }
  buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
  add_token({TokenType::STRING_LITERAL, buffer});

  consume();
  return;
}
