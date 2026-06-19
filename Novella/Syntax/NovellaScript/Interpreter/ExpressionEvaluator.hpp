#pragma once
#include <vector>
#include <string>
#include "../Expression.hpp"
#include "../Definition.hpp"

namespace Novella::Syntax::NovellaScript{

    class RuntimeEnvironment;

    class ExpressionEvaluator{

        public:

        ExpressionEvaluator() = delete;

        ExpressionEvaluator(RuntimeEnvironment& runtime)
            :
            runtime(runtime)
            {}

        UnderlyingValue evaluate(const Expression& expression) const;

        private:

        RuntimeEnvironment& runtime;

        std::vector<UnderlyingValue> evaluateFunctionArguments(const std::vector<Expression>& arguments) const;

        UnderlyingValue evaluateFunctionCall(const FunctionCallExpression& call) const;
        
        UnderlyingValue evaluateVariable(const VariableExpression& variable) const;
        UnderlyingValue evaluateLiteral(const LiteralExpression& literal) const;
    };

}