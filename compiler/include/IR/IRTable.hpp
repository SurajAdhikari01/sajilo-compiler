#pragma once

#include <algorithm>
#include <cstdint>
#include <string>

#include <vector>

struct VariableData {
  std::string name;
  uint32_t size{};
  uint32_t offset{};
};
struct FunctionData {
  uint32_t framesize{};
  std::vector<VariableData> variables;
  uint32_t offset{};
  std::string funcName{};
};
class IRTable {
public:
  FunctionData *lookup(const int index) {
    if (index < m_IRTable.size())
      return &m_IRTable[index];
    return nullptr;
  }
  FunctionData *lookup(const std::string &name) {
    auto it = std::find_if(
        m_IRTable.begin(), m_IRTable.end(),
        [&name](const auto &funcData) { return funcData.funcName == name; });
    if (it != m_IRTable.end())
      return &(*it);
    return nullptr;
  }

  VariableData *lookup_variable(const int index, const std::string &name) {
    auto funcData = lookup(index);

    if (!funcData)
      return nullptr;

    auto it = std::find_if(
        funcData->variables.begin(), funcData->variables.end(),
        [&name](const auto &variable) { return variable.name == name; });
    return (it == funcData->variables.end()) ? nullptr : &(*it);
  }

  int insert(const FunctionData &func_data) {
    m_IRTable.push_back(func_data);
    return m_IRTable.size() - 1;
  }

private:
  std::vector<FunctionData> m_IRTable;
};
inline IRTable &get_IR_Table() {
  static IRTable table;
  return table;
}
