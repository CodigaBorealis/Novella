#pragma once
#include <vector>
#include "Expression.hpp"

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment;

}

namespace Novella::NScript::Parser{

    class ExpressionEvaluator{

        public:

        ExpressionEvaluator() = delete;

        ExpressionEvaluator(Runtime::RuntimeEnvironment& runtime)
            :
            runtime(runtime)
            {}

        Value evaluate(const Expression& expression) const;

        private:

        Runtime::RuntimeEnvironment& runtime;

        std::vector<Value> evaluateFunctionArguments(const std::vector<Expression>& arguments) const;

        Value evaluateFunctionCall(const FunctionCallExpression& call) const;
        
        Value evaluateVariable(const VariableExpression& variable) const;
        Value evaluateLiteral(const LiteralExpression& literal) const;
    };

}