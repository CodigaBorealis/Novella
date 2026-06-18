#pragma once
#include "ScriptFwd.hpp"
#include "Token.hpp"
#include <memory>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    struct Value{

        enum class Type : unsigned int{

            String,
            Number,
            Boolean,
            Identifier,
            Array,
            Character
        };

        Type type;
        std::string StringValue;
        double numberValue;
        bool boolValue;
        char characterValue;

        std::vector<Value> arrayValues;
    };
    
    struct LiteralExpression{

        Value value;
    };

    struct VariableExpression{

        std::string name;
    };

    struct FunctionCallExpression{

        std::string functionName;
        std::vector<Expression> arguments;
        std::shared_ptr<Expression> answer;
    };

    struct UnaryExpression{

        Token::Type operation;
        std::shared_ptr<Expression> operand;
    };

    struct BinaryExpression{

        Token::Type operation;

        std::shared_ptr<Expression> left;
        std::shared_ptr<Expression> right;
    };            

    struct AssignmentExpression{
        
        std::shared_ptr<Expression> variable;
        std::shared_ptr<Expression> value;
    };

    struct ArrayExpression{

        std::vector<Expression> elements;
    };

    struct MemberExpression{

        std::shared_ptr<Expression> object;
        std::string member;
    };

    struct IndexExpression{

        std::shared_ptr<Expression> object;
        std::shared_ptr<Expression> index;
    };

    struct PostFixExpression{

        std::shared_ptr<Expression> operand;
        Token::Type operation;
    };
}