#pragma once
#include <optional>
#include <string>
#include <unordered_map>
enum class DataTypes { INT, STRING, USER_DEFINED, NONE };

struct decleration_data {
  DataTypes dataType = DataTypes::NONE;
  bool isConst = false;
  std::string value;
};

class SymbolTable {

public:
  std::optional<decleration_data> get(const std::string &key) {
    auto it = symbolTable.find(key);
    if (it != symbolTable.end()) {
      return it->second;
    }
    return {};
  }
  void insert(const std::string &key, const decleration_data &value) {
    symbolTable[key] = value;
  }

private:
  std::unordered_map<std::string, decleration_data> symbolTable;
};
inline SymbolTable &get_table() {
  static SymbolTable table;
  return table;
}
