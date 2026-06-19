#include "../Novella/Syntax/NovellaScript/Interpreter/ExpressionEvaluator.hpp"
#include <variant>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    std::vector<UnderlyingValue> ExpressionEvaluator::evaluateFunctionArguments(const std::vector<Expression>& arguments){

        std::vector<UnderlyingValue> runtimeValues{};

        for(const auto& parameter : arguments){

            EvaluationResult evaluated = evaluate(parameter);

            if(std::holds_alternative<UnderlyingValue>(evaluated)){

                runtimeValues.push_back(std::get<UnderlyingValue>(evaluated));

            }else if(std::holds_alternative<FunctionInvocation>(evaluated)){

                auto& invocation = std::get<FunctionInvocation>(evaluated);

                runtimeValues.push_back(evaluateReturnValue(invocation));
            }
        }

        return runtimeValues;
    }

    UnderlyingValue ExpressionEvaluator::evaluateReturnValue(const FunctionInvocation& invocation){


    }

    UnderlyingValue ExpressionEvaluator::evaluateVariable(const VariableExpression& variable){
        
        
    }

    FunctionInvocation ExpressionEvaluator::evaluateFunctionCall(const Expression& expression){

        auto& call = std::get<FunctionCallExpression>(expression);
        
        auto args = evaluateFunctionArguments(call.arguments);
        
        return FunctionInvocation{call.functionName, std::move(args)};        
    }

    EvaluationResult ExpressionEvaluator::evaluate(const Expression& expression){

        if(std::holds_alternative<FunctionCallExpression>(expression)){

            return evaluateFunctionCall(expression);

        }else if(std::holds_alternative<LiteralExpression>(expression)){

            return std::get<LiteralExpression>(expression).value.underlyingValue;

        }else if(std::holds_alternative<VariableExpression>(expression)){

            return evaluateVariable(std::get<VariableExpression>(expression));
        }

        return UnderlyingValue{PrimitiveValue{std::monostate{}}};
    }

}