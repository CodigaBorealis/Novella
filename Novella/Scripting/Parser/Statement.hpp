#pragma once
#include <variant>
#include <vector>
#include "Expression.hpp"

namespace Novella::NScript::Parser{
    
    using Expression = std::variant<LiteralExpression, VariableExpression, FunctionCallExpression,
    UnaryExpression, BinaryExpression, AssignmentExpression, ArrayExpression, MemberExpression, IndexExpression,
    PostFixExpression>;

    struct ImportStatement{

        std::string source;
        std::string alias;
    };

    struct ReturnStatement{

        Expression value;
    };

    struct IfStatement{

        Expression condition;
        std::vector<Statement> body;
        std::vector<Statement> elseBody;
    };

    struct VariableStatement{

        std::string name;
        Expression value;
    };  

    struct ExpressionStatement{

        Expression expression;
    };
}