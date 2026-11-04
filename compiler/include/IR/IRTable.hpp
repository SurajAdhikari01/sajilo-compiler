#pragma once

#include <cstdint>
#include <string>

#include <vector>

struct VariableData {
  std::string name;
  uint16_t size;
};
struct FunctionData {
  uint32_t framesize{};
  std::vector<VariableData> variables;
  uint32_t offset;
};
class IRTable {
public:
  FunctionData *lookup(const int index) {
    if (index < m_IRTable.size())
      return &m_IRTable[index];
    return nullptr;
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
