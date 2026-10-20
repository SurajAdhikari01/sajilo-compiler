#include "lexer.hpp"
#include "parser.hpp"
#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc < 2) {
    return EXIT_FAILURE;
  }
  std::filesystem::path filePath(argv[1]);
  if (filePath.extension() != ".sj") {
    std::cout << "Error: Invalid file extension. Expected a '.sj' file.\n";
    return EXIT_FAILURE;
  }
  bool isJson = false;

  OUTPUT_FORMAT file_format;

  std::string output_file;
  if (argc == 5) {
    if (!strcmp(argv[2], "-o")) {
      if (!strcmp(argv[3], "json")) {
        file_format = OUTPUT_FORMAT::json;
      } else if (!strcmp(argv[3], "text")) {
        file_format = OUTPUT_FORMAT::text;
      } else {
        file_format = OUTPUT_FORMAT::none;
        std::cout << "Specify proper file format\n";
      }
      output_file = argv[4];
    }
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
  parser.set_output_data(file_format, output_file);

  parser.set_lexer(lexer);
  parser.set_tokens(lexer.get_tokens());

  parser.parse();

  return 0;
}
