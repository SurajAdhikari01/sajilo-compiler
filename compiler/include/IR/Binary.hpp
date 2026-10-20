#pragma once

#include "Expression/BinaryExpression.hpp"
#include "IR/IR.hpp"
#include "parser.hpp"
#include "statements/statements.hpp"
#include <string>
class Binary : public IR {
public:
  Binary(BN_OPERATORS bn_operator, const std::string &oprand_left,
         const std::string &oprand_right, const std::string &res)
      : bn_operator(bn_operator), oprand_left(oprand_left),
        oprand_right(oprand_right), res(res) {}
  void generate_ir(CodeGenContext &, Parser &);

  BN_OPERATORS bn_operator;
  std::string oprand_left, oprand_right;
  std::string res;
};
