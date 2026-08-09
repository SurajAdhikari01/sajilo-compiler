#include "lexer.hpp"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }
  std::string filename(argv[1]);
  std::ifstream file(filename);
  if (!file.is_open()) {
    return EXIT_FAILURE;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();
  Lexer lexer;
  lexer.set_sourceCode(content);
  lexer.tokenize();

  return 0;
}
