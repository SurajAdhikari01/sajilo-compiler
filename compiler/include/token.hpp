#pragma once
#include <string_view>
enum class TokenType {
  // Delimiters
  LEFT_PAREN,
  RIGHT_PAREN,
  LEFT_BRACKET,
  RIGHT_BRACKET,
  LEFT_BRACE,
  RIGHT_BRACE,

  COMMA,
  DOT,
  COLON,
  SEMICOLON,
  QUESTION,

  // Arithmetic
  PLUS,
  MINUS,
  ASTERISK,
  SLASH,
  MODULO,

  INCREMENT,
  DECREMENT,

  // Assignment
  ASSIGN,
  PLUS_ASSIGN,
  MINUS_ASSIGN,
  ASTERISK_ASSIGN,
  SLASH_ASSIGN,
  MODULO_ASSIGN,

  // Comparison
  EQUAL_EQUAL,
  NOT_EQUAL,
  LESS,
  GREATER,
  LESS_EQUAL,
  GREATER_EQUAL,

  // Logical
  AND,
  OR,
  NOT,

  // Bitwise
  BIT_AND,
  BIT_OR,
  BIT_XOR,
  BIT_NOT,
  LEFT_SHIFT,
  RIGHT_SHIFT,

  // Other operators
  ARROW,

  // Language keywords
  BOL,
  SUN,
  GAR,
  JABA,
  NATRA,
  FERI,
  ROK,
  LAIJAU,
  SURU,
  DEU,
  NISKI,
  MANAU,

  WRITE,
  READ,
  FUNC,

  // Types
  KEYWORD,

  // Literal values
  TRUE,
  FALSE,
  NULL_VALUE,

  // Identifiers / literals
  IDENTIFIER,
  INT_LITERAL,
  FLOAT_LITERAL,
  CHAR_LITERAL,
  STRING_LITERAL,

  // Special
  UNKNOWN,
  NONE,
  END_OF_FILE
};
struct Token {
  Token() {}
  constexpr Token(TokenType token, std::string_view value)
      : token{token}, value{value} {}
  constexpr Token(TokenType token) : token{token} {}
  TokenType token;
  std::string_view value;
  int line_number = 1;
  int current_column = 0;
};
