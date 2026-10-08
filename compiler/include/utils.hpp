#pragma once

#include <cstdint>
#include <string>
#include <string_view>

enum class PRIMITIVE_DATA_TYPES {
  INT,
  CHAR,
  VOID,
  FLOAT,
  BOOL,
  STRING,
  IDENTIFIER,
  UNEXPECTED,
  USER_DEFINED,
};

struct SourceLocation {
  uint32_t line{};
  uint32_t col{};
};

struct TypeRef {
  PRIMITIVE_DATA_TYPES data_type = PRIMITIVE_DATA_TYPES::VOID;
  std::string_view name;
};

struct ParameterDecl {
  TypeRef type;
  std::string_view name;
};

inline PRIMITIVE_DATA_TYPES get_datatypes(const std::string_view keyword) {
  constexpr static std::pair<std::string, PRIMITIVE_DATA_TYPES>
      m_datatype_map[] = {
          {"int", PRIMITIVE_DATA_TYPES::INT},
          {"void", PRIMITIVE_DATA_TYPES::VOID},
          {"char", PRIMITIVE_DATA_TYPES::CHAR},
          {"float", PRIMITIVE_DATA_TYPES::FLOAT},
          {"bool", PRIMITIVE_DATA_TYPES::BOOL},
      };
  for (const auto &[view, data_type] : m_datatype_map) {
    if (view == keyword) {
      return data_type;
    }
  }
  return PRIMITIVE_DATA_TYPES::USER_DEFINED;
}

using DATATYPES_COMPATIBILITY_VALUE = uint16_t;
enum class DATATYPE_COMPATABILITY : DATATYPES_COMPATIBILITY_VALUE {
  VOID = 0,
  INT = 1 << 1,
  FLOAT = 1 << 2,
  DOUBLE = 1 << 3,
  BINARY = 1 << 4,
  HEX = 1 << 5,
};

inline DATATYPE_COMPATABILITY
get_datatype_compatability_from_primitive(PRIMITIVE_DATA_TYPES primitive_type) {
  switch (primitive_type) {
  case PRIMITIVE_DATA_TYPES::INT:
    return DATATYPE_COMPATABILITY::INT;

  default:
    break;
  }
  return DATATYPE_COMPATABILITY::VOID;
}

// inline DATATYPE_COMPATABILITY operator|(DATATYPE_COMPATABILITY lhs,
// DATATYPE_COMPATABILITY rhs)
// {
// }

inline bool is_compatible_datatype(PRIMITIVE_DATA_TYPES primitive,
                                   PRIMITIVE_DATA_TYPES primary) {
  auto primary_to_datatype_compatibility =
      get_datatype_compatability_from_primitive(primary);
  auto primitive_to_datatype_compatibility =
      get_datatype_compatability_from_primitive(primitive);
  return static_cast<int>(primary_to_datatype_compatibility) &
         static_cast<int>(primitive_to_datatype_compatibility);
};
inline std::string string_view_to_string(std::string_view sv) {
  return std::string(sv);
}
class Parser;
void print_error(const Parser &parser, std::string_view error_msg);
void print_error(const Parser &parser, std::string_view error_msg,
                 const SourceLocation &);
