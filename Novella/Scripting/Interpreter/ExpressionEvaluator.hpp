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

        Parser::Value evaluateAddition(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateSubstraction(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateMultiplication(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateDivision(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateModulo(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateLess(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateLessEquals(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateGreater(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateGreaterEquals(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateEquals(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateNotEquals(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateAnd(const Parser::Value& firstValue, const Parser::Value& secondValue);
        Parser::Value evaluateOr(const Parser::Value& firstValue, const Parser::Value& secondValue);

        Parser::Value evaluateBinaryExpression(const Parser::BinaryExpression& binaryExpression);

        Parser::Value evaluateAssignmentExpression(const Parser::AssignmentExpression& AssignmentExpression);

        template<typename T, typename Function>
        
        Parser::Value applyPrimitiveOperation(const Parser::Value& value, Function&& operation, const std::string& errorMessage){

            if(!std::holds_alternative<Parser::PrimitiveValue>(value.underlyingValue)) throw std::runtime_error("Cannot apply operation to array structures");

            const auto& primitive = std::get<Parser::PrimitiveValue>(value.underlyingValue);

            if(!std::holds_alternative<T>(primitive)) throw std::runtime_error(errorMessage);

            Parser::Value result{};

            result.underlyingValue = Parser::PrimitiveValue{operation(std::get<T>(primitive))};;

            return result;
        }

        template<typename T, typename Function>
        
        Parser::Value applyPrimitiveOperation(const Parser::Value& first, const Parser::Value& second, Function&& operation, const std::string& errorMessage){

            if(!std::holds_alternative<Parser::PrimitiveValue>(first.underlyingValue) || !std::holds_alternative<Parser::PrimitiveValue>(second.underlyingValue)) throw std::runtime_error("Cannot apply binary operation to array structures");

            const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(first.underlyingValue);
            
            const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(second.underlyingValue);

            if(!std::holds_alternative<T>(primitiveFirst) || !std::holds_alternative<T>(primitiveSecond)) throw std::runtime_error(errorMessage);

            Parser::Value result{};

            result.underlyingValue = Parser::PrimitiveValue{operation(std::get<T>(primitiveFirst), std::get<T>(primitiveSecond))};;

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
        
        Parser::Value evaluateIndexExpression(const Parser::IndexExpression& indexExpression);
        Parser::Value evaluateArrayExpression(const Parser::ArrayExpression& ArrayExpression);

        Parser::Value evaluatePostFixExpression(const Parser::PostFixExpression& postFixExpression);
        
        size_t callStackDepth = 0;

        const size_t MAX_CALL_STACK = 500;
    };

}