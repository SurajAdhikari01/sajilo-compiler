#include "lexer.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }
  std::filesystem::path filePath(argv[1]);
  if (filePath.extension() != ".sj") {
    std::cout << "Error: Invalid file extension. Expected a '.sj' file.\n";
    return EXIT_FAILURE;
  }
  std::ifstream file(filePath);

  if (!file.is_open()) {
    return EXIT_FAILURE;
  }
  std::stringstream buffer;
  buffer << file.rdbuf();
  std::string content = buffer.str();
  Lexer lexer;
  lexer.set_filename(filePath.filename().string());
  lexer.set_sourceCode(content);
  lexer.tokenize();

  Parser parser;

  parser.set_lexer(lexer);
  parser.set_tokens(lexer.get_tokens());

  parser.parse();

  return 0;
}
