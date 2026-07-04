#include "../Novella/Scripting/Interpreter/ExpressionEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include <variant>
#include <vector>

namespace Novella::NScript::Runtime{

    void ExpressionEvaluator::setFunctionExecutor(FunctionExecutor& executor){

        this->functionExecutor = &executor;
    }

    std::vector<Parser::Value> ExpressionEvaluator::evaluateFunctionArguments(const std::vector<Parser::Expression>& arguments) const{

        std::vector<Parser::Value> values{};

        values.reserve(arguments.size());

        for(const auto& argument : arguments){

            values.push_back(evaluate(argument));
        }

        return values;
    }

    Parser::Value ExpressionEvaluator::evaluateVariable(const Parser::VariableExpression& variable) const{
        
        return runtime.getVariable(variable.name);
    }

    Parser::Value ExpressionEvaluator::evaluateFunctionCall(const Parser::FunctionCallExpression& call) const{

        auto args = evaluateFunctionArguments(call.arguments);

        return functionExecutor->call(call.functionName, args);
    }

    Parser::Value ExpressionEvaluator::evaluate(const Parser::Expression& expression) const{

        if(auto functionCall = std::get_if<Parser::FunctionCallExpression>(&expression)){

            return evaluateFunctionCall(*functionCall);

        }else if(auto literal = std::get_if<Parser::LiteralExpression>(&expression)){

            return literal->value;

        }else if(auto variable = std::get_if<Parser::VariableExpression>(&expression)){

            return evaluateVariable(*variable);

        }else if(auto unary = std::get_if<Parser::UnaryExpression>(&expression)){


        }else if(auto binary = std::get_if<Parser::BinaryExpression>(&expression)){


        }else if(auto assignment = std::get_if<Parser::AssignmentExpression>(&expression)){


        }else if(auto array = std::get_if<Parser::ArrayExpression>(&expression)){


        }else if(auto member = std::get_if<Parser::MemberExpression>(&expression)){


        }else if(auto index = std::get_if<Parser::IndexExpression>(&expression)){


        }else if(auto postFix = std::get_if<Parser::PostFixExpression>(&expression)){


        }

        return Parser::Value{Parser::PrimitiveValue{std::monostate{}}};
    }

}