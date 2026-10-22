#pragma once

#include "IR/DataItem.hpp"
#include <cstddef>
#include <cstdint>
#include <format>
#include <string>
#include <string_view>
#include <utility>
#include <vector>
struct CodeGenContext;
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
  SourceLocation location;
};

inline PRIMITIVE_DATA_TYPES get_datatypes(const std::string_view keyword) {
  constexpr static std::pair<std::string, PRIMITIVE_DATA_TYPES>
      m_datatype_map[] = {
          {"int", PRIMITIVE_DATA_TYPES::INT},
          {"void", PRIMITIVE_DATA_TYPES::VOID},
          {"char", PRIMITIVE_DATA_TYPES::CHAR},
          {"float", PRIMITIVE_DATA_TYPES::FLOAT},
          {"bool", PRIMITIVE_DATA_TYPES::BOOL},
          {"string", PRIMITIVE_DATA_TYPES::STRING},
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
  CHAR = 1 << 6,
  STRING = 1 << 7,
};

inline DATATYPE_COMPATABILITY
get_datatype_compatability_from_primitive(PRIMITIVE_DATA_TYPES primitive_type) {
  switch (primitive_type) {
  case PRIMITIVE_DATA_TYPES::INT:
    return DATATYPE_COMPATABILITY::INT;
  case PRIMITIVE_DATA_TYPES::CHAR:
    return DATATYPE_COMPATABILITY::CHAR;
  case PRIMITIVE_DATA_TYPES::STRING:
    return DATATYPE_COMPATABILITY::STRING;

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
void print_error(Parser &parser, std::string_view error_msg);
void print_error(Parser &parser, std::string_view error_msg,
                 const SourceLocation &);

inline std::string
generate_function_label(std::string_view name,
                        std::vector<ParameterDecl> parameters) {
  std::string parameters_str;
  for (size_t i = 0; i < parameters.size(); i++) {
    parameters_str += parameters[i].type.name;
    if (i < (parameters.size() - 1)) {
      parameters_str += ',';
    }
  }

  return std::format("{}({})", name, parameters_str);
}

inline std::vector<std::string_view> str_datas;
inline size_t store_string_literal(std::string_view str_data) {
  str_datas.push_back(str_data);
  return str_datas.size() - 1;
}

void add_string_literal_instruction(CodeGenContext &context, Parser &parser);
