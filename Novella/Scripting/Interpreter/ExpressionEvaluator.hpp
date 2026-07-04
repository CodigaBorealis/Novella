#pragma once
#include <vector>
#include "../Parser/Expression.hpp"

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment;

    class FunctionExecutor;

    class ExpressionEvaluator{

        public:

        ExpressionEvaluator() = delete;

        ExpressionEvaluator(Runtime::RuntimeEnvironment& runtime)
            :
            runtime(runtime)
            {}

        Parser::Value evaluate(const Parser::Expression& expression) const;

        void setFunctionExecutor(FunctionExecutor& executor);

        private:

        Runtime::RuntimeEnvironment& runtime;
        FunctionExecutor* functionExecutor = nullptr;
        std::vector<Parser::Value> evaluateFunctionArguments(const std::vector<Parser::Expression>& arguments) const;

        Parser::Value evaluateFunctionCall(const Parser::FunctionCallExpression& call) const;
        
        Parser::Value evaluateVariable(const Parser::VariableExpression& variable) const;
        Parser::Value evaluateLiteral(const Parser::LiteralExpression& literal) const;
    };

}