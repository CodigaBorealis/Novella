#include "../Novella/Scripting/Interpreter/ExpressionEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include <stdexcept>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>
#include <iostream>

namespace Novella::NScript::Runtime{

    void ExpressionEvaluator::setFunctionExecutor(FunctionExecutor& executor){

        this->functionExecutor = &executor;
    }

    std::vector<Parser::Value> ExpressionEvaluator::evaluateFunctionArguments(const std::vector<Parser::Expression>& arguments){

        std::vector<Parser::Value> values{};

        values.reserve(arguments.size());

        for(const auto& argument : arguments){

            values.push_back(evaluate(argument));
        }

        return values;
    }

    Parser::Value ExpressionEvaluator::evaluateVariable(const Parser::VariableExpression& variable){
        
        return runtime.getVariable(variable.name);
    }

    Parser::Value ExpressionEvaluator::evaluateFunctionCall(const Parser::FunctionCallExpression& call){

        if(callStackDepth >= MAX_CALL_STACK) throw std::runtime_error("NovellaScript Runtime Error: Stack overflow detected, infinite recursion suspected in function: " + call.functionName);
        
        CallStackGuard guard(callStackDepth);
        
        auto args = evaluateFunctionArguments(call.arguments);
        
        std::string targetName = "";

        if(call.answer){

            if(auto variableExpression = std::get_if<Parser::VariableExpression>(call.answer.get())){

                targetName = variableExpression->name;

            }else if(auto memberExpression = std::get_if<Parser::MemberExpression>(call.answer.get())){

                if(auto objectVar = std::get_if<Parser::VariableExpression>(memberExpression->object.get())){

                    targetName = objectVar->name;

                }else{

                    targetName = memberExpression->member;
                }
            }
        }

        return functionExecutor->call(call.functionName, args);
    }

    Parser::Value ExpressionEvaluator::applyIncrement(const Parser::Value& value){

        return applyPrimitiveOperation<double>(value,[](double v){

            return v + 1.0;

        }, "Cannot increment non-numeric type");
    }

    Parser::Value ExpressionEvaluator::applyDecrement(const Parser::Value& value){

        return applyPrimitiveOperation<double>(value,[](double v){

            return v - 1.0;
            
        }, "Cannot decrement non-numeric type");

    }

    Parser::Value ExpressionEvaluator::applyMinus(const Parser::Value& value){

        return applyPrimitiveOperation<double>(value,[](double v){

            return v * -1.0;
            
        }, "Cannot apply minus to non-numeric type");

    }

    Parser::Value ExpressionEvaluator::applyNot(const Parser::Value& value){

        return applyPrimitiveOperation<bool>(value,[](bool v){

            return !v;
            
        }, "Cannot apply not to non-boolean type");

    }

    Parser::Value ExpressionEvaluator::evaluateUnaryExpression(const Parser::UnaryExpression& unaryExpression){

        auto value = evaluate(*unaryExpression.operand);

        if(unaryExpression.operation == Parser::Token::Type::Increment){
            
            return applyIncrement(value);

        }else if(unaryExpression.operation == Parser::Token::Type::Decrement){

            return applyDecrement(value);

        }else if(unaryExpression.operation == Parser::Token::Type::Minus){

            return applyMinus(value);

        }else if(unaryExpression.operation == Parser::Token::Type::Not){

            return applyNot(value);
        }

        throw std::runtime_error("Invalid unary operand type" + std::to_string(static_cast<int>(unaryExpression.operation)));
    }

    Parser::Value ExpressionEvaluator::evaluate(const Parser::Expression& expression){

        if(auto functionCall = std::get_if<Parser::FunctionCallExpression>(&expression)){
            
            return evaluateFunctionCall(*functionCall);

        }else if(auto literal = std::get_if<Parser::LiteralExpression>(&expression)){

            return literal->value;

        }else if(auto variable = std::get_if<Parser::VariableExpression>(&expression)){

            return evaluateVariable(*variable);

        }else if(auto unary = std::get_if<Parser::UnaryExpression>(&expression)){   

            if(auto literal = std::get_if<Parser::LiteralExpression>(unary->operand.get())){

                return evaluateUnaryExpression(*unary);

            }else if(auto variable = std::get_if<Parser::VariableExpression>(unary->operand.get())){

                std::string name = variable->name;

                Parser::Value currentValue = runtime.getVariable(name);

                Parser::Value newValue{};

                if(unary->operation == Parser::Token::Type::Increment){

                    newValue = applyIncrement(currentValue);

                }else if(unary->operation == Parser::Token::Type::Decrement){

                    newValue = applyDecrement(currentValue);

                }else if(unary->operation == Parser::Token::Type::Minus){

                    newValue = applyMinus(currentValue);

                }else if(unary->operation == Parser::Token::Type::Not){

                    newValue = applyNot(currentValue);
                }

                runtime.setVariable(name, newValue);

                return newValue;
            }

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