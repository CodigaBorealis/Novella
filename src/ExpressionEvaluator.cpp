#include "../Novella/Syntax/NovellaScript/Interpreter/ExpressionEvaluator.hpp"
#include "../Novella/Syntax/NovellaScript/Interpreter/RuntimeEnvironment.hpp"
#include <variant>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    std::vector<UnderlyingValue> ExpressionEvaluator::evaluateFunctionArguments(const std::vector<Expression>& arguments) const{

        std::vector<UnderlyingValue> values{};

        values.reserve(arguments.size());

        for(const auto& argument : arguments){

            values.push_back(evaluate(argument));
        }

        return values;
    }

    UnderlyingValue ExpressionEvaluator::evaluateVariable(const VariableExpression& variable) const{
        
        return runtime.getVariable(variable.name);
    }

    UnderlyingValue ExpressionEvaluator::evaluateFunctionCall(const FunctionCallExpression& call) const{

        auto args = evaluateFunctionArguments(call.arguments);

        return runtime.invokeFunction(call.functionName, args);
    }

    UnderlyingValue ExpressionEvaluator::evaluate(const Expression& expression) const{

        if(auto functionCall = std::get_if<FunctionCallExpression>(&expression)){

            return evaluateFunctionCall(*functionCall);

        }else if(auto literal = std::get_if<LiteralExpression>(&expression)){

            return literal->value.underlyingValue;

        }else if(auto variable = std::get_if<VariableExpression>(&expression)){

            return evaluateVariable(*variable);
        }

        return UnderlyingValue{PrimitiveValue{std::monostate{}}};
    }

}