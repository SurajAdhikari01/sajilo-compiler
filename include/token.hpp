#pragma once
#include <string_view>
enum class TokenName {

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

  // Arithmetic
  PLUS,
  MINUS,
  STAR,
  SLASH,
  MODULO,

  INCREMENT,
  DECREMENT,

  // Assignment
  ASSIGN,
  PLUS_ASSIGN,
  MINUS_ASSIGN,
  STAR_ASSIGN,
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

  // Keywords
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

  // Types
  INT,
  FLOAT,
  CHAR,
  STRING,
  BOOL,

  // Values
  TRUE,
  FALSE,
  NULL_VALUE,

  // Identifiers & literals
  IDENTIFIER,
  INT_LITERAL,
  FLOAT_LITERAL,
  CHAR_LITERAL,
  STRING_LITERAL,

  // Special
  ARROW,
  QUESTION,
  UNKNOWN
};
struct Token {
  Token() {}
  Token(TokenName token, std::string_view value) : token{token}, value{value} {}
  constexpr Token(TokenName token) : token{token} {}

  TokenName token;
  std::string_view value;
};
