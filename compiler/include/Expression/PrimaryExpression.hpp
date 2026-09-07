#include "Expression/Expression.hpp"
#include "parser.hpp"
#include <memory>

class PrimaryExpression : public Expression {
public:
  static std::unique_ptr<Expression> parse_primary(Parser &parser);

private:
  enum class PRIMARY_TYPE {
    INT_LITERAL,
    STRING_LITERAL,
    IDENTIFIER,
    NONE
  } primary_type = PRIMARY_TYPE::NONE;
  std::string_view value;
};
