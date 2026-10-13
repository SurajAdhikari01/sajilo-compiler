#pragma once
#include "utils.hpp"
#include <optional>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>
//
struct decleration_data {
  TypeRef type;
  bool isConst = false;
  std::string value;
};

class SymbolTable {

public:
  std::optional<decleration_data> lookup(const std::string_view key) {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); ++it) {
      if (it->second) {
        auto &map = it->first;
        auto m_it = map.find(key);

        if (m_it != map.end()) {
          return m_it->second;
        }
      }
    }

    return {};
  }
  bool insert(const std::string_view key, const decleration_data &value) {
    if (find(key)) {
      return false;
    }
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); ++it) {
      if (it->second) {
        auto &map = it->first;
        map[key] = value;
        return true;
      }
    }
    return false;
  }

  bool find(std::string_view key) {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); ++it) {
      if (it->second) {
        auto &map = it->first;
        auto it = map.find(key);
        if (it != map.end()) {
          return true;
        }
      }
    }
    return false;
  }

  void enter_scope() {
    symbolTable.push_back({});
    symbolTable.back().second = true;
  };
  void exit_scope() {
    for (auto it = symbolTable.rbegin(); it != symbolTable.rend(); it++) {
      if (it->second) {
        it->second = false;
        break;
      }
    }
  }
  friend SymbolTable &get_table();

private:
  SymbolTable() { symbolTable.push_back({}); }
  std::vector<
      std::pair<std::unordered_map<std::string_view, decleration_data>, bool>>
      symbolTable;
};
inline SymbolTable &get_table() {
  static SymbolTable table;
  return table;
}
