#pragma once
#include <vector>
#include <string>
#include "../Expression.hpp"

namespace Novella::Syntax::NovellaScript{

    struct FunctionInvocation{

        std::string name;
        std::vector<UnderlyingValue> arguments;
    };

    using EvaluationResult = std::variant<UnderlyingValue, FunctionInvocation>;

    class ExpressionEvaluator{

        public:

        EvaluationResult evaluate(const Expression& expression);

        private:

        std::vector<UnderlyingValue> evaluateFunctionArguments(const std::vector<Expression>& arguments);

        FunctionInvocation evaluateFunctionCall(const Expression& expression);
        UnderlyingValue evaluateReturnValue(const FunctionInvocation& invocation);
        
        UnderlyingValue evaluateVariable(const VariableExpression& variable);
        UnderlyingValue evaluateLiteral(const LiteralExpression& literal);
    };

}