#pragma once

#include "statements/statements.hpp"
#include <string_view>
class IR {
  std::string_view IR_generation(CodeGenContext);
};
