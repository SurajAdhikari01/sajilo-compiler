#include "lexer.hpp"
#include "token.hpp"
#include <string_view>

static bool isKeyword(const std::string_view value, Token &token) {
  constexpr static std::pair<std::string_view, Token> keyword_map[] = {
      {"suru", {TokenName::SURU}},     {"read", {TokenName::READ}},
      {"write", {TokenName::WRITE}},   {"jaba", {TokenName::JABA}},
      {"laijau", {TokenName::LAIJAU}}, {"natra", {TokenName::NATRA}},
      {"deu", {TokenName::DEU}},       {"int", {TokenName::KEYWORD, "int"}},
      {"niski", {TokenName::NISKI}},   {"func", {TokenName::FUNC}},
      {"manau", {TokenName::MANAU}},

  };
  for (const auto &[map_view, map_token] : keyword_map) {
    if (map_view == value) {
      token = map_token;
      return true;
    }
  }
  return false;
}

void Lexer::set_sourceCode(std::string &data) {
  this->source_code = std::move(data);
}

void Lexer::tokenize() {
  for (; index < source_code.size(); index++) {
    const char c = source_code[index];
    if (!scan_character(c)) {
      process_keyword(c);
    }
  }
}

bool Lexer::scan_character(const char c) {
  switch (c) {

  case '(':
    add_token({TokenName::LEFT_PAREN});
    return true;

  case ')':
    add_token({TokenName::RIGHT_PAREN});
    return true;

  case '[':
    add_token({TokenName::LEFT_BRACKET});
    return true;

  case ']':
    add_token({TokenName::RIGHT_BRACKET});
    return true;

  case '{':
    add_token({TokenName::LEFT_BRACE});
    return true;

  case '}':
    add_token({TokenName::RIGHT_BRACE});
    return true;

  case ',':
    add_token({TokenName::COMMA});
    return true;

  case '.':
    add_token({TokenName::DOT});
    return true;

  case ':':
    add_token({TokenName::COLON});
    return true;

  case ';':
    add_token({TokenName::SEMICOLON});
    return true;

  case '?':
    add_token({TokenName::QUESTION});
    return true;

  case '+':
    add_token({TokenName::PLUS});
    return true;
  case '-':
    if ('>' == peek()) {
      consume();
      add_token({TokenName::ARROW});
    } else {
      add_token({TokenName::MINUS});
    }
    return true;

  case '*':
    add_token({TokenName::STAR});
    return true;
  case '/':
    add_token({TokenName::SLASH});
    return true;

  case '#':
    while (peek() != '\n') {
      consume();
    }
    consume();
    return true;

  case '"':
    process_string_literal();
    return true;
  case '=':
    add_token({TokenName::ASSIGN});
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
  char *first_ptr = get_current_ptr();
  if (isChar(c)) {
    while (isChar(peek()) || isNum(peek())) {
      consume();
    }
    buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
    if (Token token; isKeyword(buffer, token)) {
      add_token(token);
    } else {
      add_token({TokenName::IDENTIFIER, buffer});
    }
  }
  if (isNum(c)) {
    first_ptr = get_current_ptr();

    while (isNum(peek())) {
      consume();
    }
    buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
    add_token({TokenName::INT_LITERAL, buffer});
  }
};

void Lexer::process_string_literal() {
  if (peek() == '"') {
    add_token({TokenName::STRING_LITERAL});
    consume();
    return;
  }

  consume();
  char *first_ptr = get_current_ptr();
  while (peek() != '"' && peek() != '\0') {
    consume();
  }
  buffer = std::string_view(first_ptr, get_current_ptr() - first_ptr + 1);
  add_token({TokenName::STRING_LITERAL, buffer});

  consume();
  return;
}
