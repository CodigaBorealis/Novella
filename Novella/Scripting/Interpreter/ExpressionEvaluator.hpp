#pragma once
#include <cstddef>
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

        Parser::Value evaluate(const Parser::Expression& expression);

        void setFunctionExecutor(FunctionExecutor& executor);

        private:

        class CallStackGuard{

            public:
            CallStackGuard(size_t& depth)
            :
            depth(depth){

                depth++;
            }

            ~CallStackGuard(){

                depth --;
            }
            
            private:

            size_t& depth;            
        };

        Runtime::RuntimeEnvironment& runtime;
        FunctionExecutor* functionExecutor = nullptr;
        std::vector<Parser::Value> evaluateFunctionArguments(const std::vector<Parser::Expression>& arguments);

        Parser::Value evaluateFunctionCall(const Parser::FunctionCallExpression& call);
        
        Parser::Value evaluateVariable(const Parser::VariableExpression& variable);
        Parser::Value evaluateLiteral(const Parser::LiteralExpression& literal);

        size_t callStackDepth = 0;

        const size_t MAX_CALL_STACK = 500;
    };

}