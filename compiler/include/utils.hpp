#pragma once

#include <string>
#include <string_view>
enum class DATA_TYPES {
  INT,
  CHAR,
  VOID,
  FLOAT,
  BOOL,
  USER_DEFINED,

};
inline DATA_TYPES get_datatypes(const std::string_view keyword) {
  constexpr static std::pair<std::string, DATA_TYPES> m_datatype_map[] = {
      {"int", DATA_TYPES::INT},   {"void", DATA_TYPES::VOID},
      {"char", DATA_TYPES::CHAR}, {"float", DATA_TYPES::FLOAT},
      {"bool", DATA_TYPES::BOOL},
  };
  for (const auto &[view, data_type] : m_datatype_map) {
    if (view == keyword) {
      return data_type;
    }
  }
  return DATA_TYPES::USER_DEFINED;
}

inline std::string string_view_to_string(std::string_view sv) {
  return std::string(sv);
}
class Parser;
void print_error(const Parser &parser, std::string_view error_msg);
