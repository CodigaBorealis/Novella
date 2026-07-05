#pragma once
#include <cstddef>
#include <stdexcept>
#include <variant>
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

        template<typename T, typename Function>

        Parser::Value applyPrimitiveOperation(const Parser::Value& value, Function&& operation, const std::string& errorMessage){

            if(!std::holds_alternative<Parser::PrimitiveValue>(value.underlyingValue)) throw std::runtime_error("Cannot apply operation to array structures");

            const auto& primitive = std::get<Parser::PrimitiveValue>(value.underlyingValue);

            if(!std::holds_alternative<T>(primitive)) throw std::runtime_error(errorMessage);

            Parser::Value result{};

            result.underlyingValue = Parser::PrimitiveValue{operation(std::get<T>(primitive))};;

            return result;
        }

        Parser::Value evaluateUnaryExpression(const Parser::UnaryExpression& unaryExpression);

        Parser::Value applyIncrement(const Parser::Value& value);
        Parser::Value applyDecrement(const Parser::Value& value);
        Parser::Value applyMinus(const Parser::Value& value);
        Parser::Value applyNot(const Parser::Value& value);

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