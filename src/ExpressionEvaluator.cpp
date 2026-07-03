#include "../Novella/Scripting/Parser/ExpressionEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include <variant>
#include <vector>

namespace Novella::NScript::Parser{

    std::vector<Value> ExpressionEvaluator::evaluateFunctionArguments(const std::vector<Expression>& arguments) const{

        std::vector<Value> values{};

        values.reserve(arguments.size());

        for(const auto& argument : arguments){

            values.push_back(evaluate(argument));
        }

        return values;
    }

    Value ExpressionEvaluator::evaluateVariable(const VariableExpression& variable) const{
        
        return runtime.getVariable(variable.name);
    }

    Value ExpressionEvaluator::evaluateFunctionCall(const FunctionCallExpression& call) const{

        auto args = evaluateFunctionArguments(call.arguments);

        FunctionDefinition function = runtime.getFunction(call.functionName);
        
        return Value{};
    }

    Value ExpressionEvaluator::evaluate(const Expression& expression) const{

        if(auto functionCall = std::get_if<FunctionCallExpression>(&expression)){

            return evaluateFunctionCall(*functionCall);

        }else if(auto literal = std::get_if<LiteralExpression>(&expression)){

            return literal->value;

        }else if(auto variable = std::get_if<VariableExpression>(&expression)){

            return evaluateVariable(*variable);
        }

        return Value{PrimitiveValue{std::monostate{}}};
    }

}