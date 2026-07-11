#include "../Novella/Scripting/Interpreter/ExpressionEvaluator.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include <cmath>
#include <cstddef>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <variant>
#include <vector>

namespace Novella::NScript::Runtime{

    void ExpressionEvaluator::setFunctionExecutor(FunctionExecutor& executor){

        this->functionExecutor = &executor;
    }

    std::string ExpressionEvaluator::substractStrings(const std::string& a, const std::string& b){

        std::unordered_map<char, int> counts;

        for(char c : b){

            counts[c] ++;
        }

        std::string result;

        for(char c : a){

            if(counts[c] > 0){

                counts[c]--;

            }else{

                result+=c;
            }
        }
                
        return result;

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

        if(auto variable = std::get_if<Parser::VariableExpression>(unaryExpression.operand.get())){

            std::string name = variable->name;
            Parser::Value currentValue = runtime.getVariable(name);

            if(unaryExpression.operation == Parser::Token::Type::Increment){

                Parser::Value newValue = applyIncrement(currentValue);

                runtime.setVariable(name, newValue);

                return newValue;

            }else if(unaryExpression.operation == Parser::Token::Type::Decrement){

                Parser::Value newValue = applyDecrement(currentValue);

                runtime.setVariable(name, newValue);

                return newValue;

            }else if(unaryExpression.operation == Parser::Token::Type::Minus){

                return applyMinus(currentValue);

            }else if(unaryExpression.operation == Parser::Token::Type::Not){

                return applyNot(currentValue);
            }

        }else if(auto indexExpression = std::get_if<Parser::IndexExpression>(unaryExpression.operand.get())){

            if(auto variable = std::get_if<Parser::VariableExpression>(indexExpression->object.get())){

                std::string variableName = variable->name;

                Parser::Value entireArray = runtime.getVariable(variableName);

                Parser::Value indexResponse = evaluate(*indexExpression->index);
                
                size_t targetIndex = static_cast<size_t>(indexResponse.get<double>());

                auto& elements = std::get<std::vector<Parser::PrimitiveValue>>(entireArray.underlyingValue);

                if(targetIndex >= elements.size()) throw std::runtime_error("NovellaScript Runtime Error: Index out of bounds");

                Parser::Value elementValue{};

                elementValue.underlyingValue = elements[targetIndex];

                if(unaryExpression.operation == Parser::Token::Type::Increment){

                    Parser::Value newValue = applyIncrement(elementValue);

                    elements[targetIndex] = std::get<Parser::PrimitiveValue>(newValue.underlyingValue);

                    runtime.setVariable(variableName, entireArray);

                    return newValue;

                }else if(unaryExpression.operation == Parser::Token::Type::Decrement){

                    Parser::Value newValue = applyDecrement(elementValue);

                    elements[targetIndex] = std::get<Parser::PrimitiveValue>(newValue.underlyingValue);

                    runtime.setVariable(variableName, entireArray);

                    return newValue;

                }else if(unaryExpression.operation == Parser::Token::Type::Minus){

                    return applyMinus(elementValue);

                }else if(unaryExpression.operation == Parser::Token::Type::Not){

                    return applyNot(elementValue);
                }
        
            }
        }else if(auto literal = std::get_if<Parser::LiteralExpression>(unaryExpression.operand.get())){

            Parser::Value value = evaluateLiteral(*literal);

            if(unaryExpression.operation == Parser::Token::Type::Minus) return applyMinus(value);

            if(unaryExpression.operation == Parser::Token::Type::Not) return applyNot(value);

            return value;

        }else if(auto memberExpression = std::get_if<Parser::FunctionCallExpression>(unaryExpression.operand.get())){

            Parser::Value value = evaluate(*memberExpression);

            if(unaryExpression.operation == Parser::Token::Type::Minus) return applyMinus(value);

            if(unaryExpression.operation == Parser::Token::Type::Not) return applyNot(value);

            return value;

        }
        
        throw std::runtime_error("Invalid unary operand type" + std::to_string(static_cast<int>(unaryExpression.operation)));
    }

    Parser::Value ExpressionEvaluator::evaluateAssignmentExpression(const Parser::AssignmentExpression& AssignmentExpression){

        Parser::Value newValue = evaluate(*AssignmentExpression.value);

        if(auto variableExpression = std::get_if<Parser::VariableExpression>(AssignmentExpression.variable.get())){

            std::string variableName = variableExpression->name;

            runtime.setVariable(variableName, newValue);

            return newValue;
        }

        throw std::runtime_error("Invalid assignment target expression");
    }

    Parser::Value ExpressionEvaluator::evaluateAddition(const Parser::Value& firstValue, const Parser::Value& secondValue){
        
        const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(firstValue.underlyingValue);
        const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(secondValue.underlyingValue);

        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<bool>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, bool>(firstValue, secondValue,[](std::string  a, bool b){

                if(b) return a + "true";

                return a + "false";
                
            }, "Type Mismatch: Unsuported addition or concatenation operation");

        }

        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<double>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, double>(firstValue, secondValue,[](std::string  a, double b){

                return a + std::to_string(b);
                
            }, "Type Mismatch: Unsuported addition or concatenation operation");

        }

        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<std::string>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, std::string>(firstValue, secondValue,[](std::string  a, std::string b){

                return a + b;
                
            }, "Type Mismatch: Unsuported addition or concatenation operation");

        }

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a + b;
            
        }, "Type Mismatch: Unsuported addition or concatenation operation");
    }

    Parser::Value ExpressionEvaluator::evaluateSubstraction(const Parser::Value& firstValue, const Parser::Value& secondValue){

        const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(firstValue.underlyingValue);
        const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(secondValue.underlyingValue);
        
        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<std::string>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, std::string>(firstValue, secondValue,[this](std::string  a, std::string b){

                return substractStrings(a, b);
                
            }, "Type Mismatch: substraction requires two numeric operands or two string operands");

        }

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a - b;
            
        }, "Type Mismatch: substraction requires two numeric operands or two string operands");

    }

    Parser::Value ExpressionEvaluator::evaluateMultiplication(const Parser::Value& firstValue, const Parser::Value& secondValue){

        const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(firstValue.underlyingValue);
        const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(secondValue.underlyingValue);
        
        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<double>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, double>(firstValue, secondValue,[](std::string  a, double b){

                if(b < 0) throw std::runtime_error("Cannot multiply a string by a negative integer");

                if(b != std::floor(b)) throw std::runtime_error("Multiplying a string requires an integer as the second operand");

                if(!std::isfinite(b)) throw std::runtime_error("Multiplier must be a finite integer");

                size_t count = static_cast<size_t>(b);

                std::string result;
                
                result.reserve(a.size() * count);

                for(size_t x = 0; x < count ; x ++){

                    result += a;
                }
                
                return result;

            }, "Type Mismatch: substraction requires two numeric operands or two string operands");

        }

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a * b;
            
        }, "Type Mismatch: multiplication requires two numeric operands");
    }

    Parser::Value ExpressionEvaluator::evaluateDivision(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a / b;
            
        }, "Type Mismatch: division requires two numeric operands");
    }

    Parser::Value ExpressionEvaluator::evaluateModulo(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){
            
            if(a != std::floor(a) || b != std::floor(b)) throw std::runtime_error("modulo requires two integer operands");

            return static_cast<double>(static_cast<int>(a) % static_cast<int>(b));
            
        }, "Type Mismatch: modulo requires two integer operands");
    }

    Parser::Value ExpressionEvaluator::evaluateLess(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a < b;
            
        }, "Type Mismatch: lessThan requires two numeric operands");
    }

    Parser::Value ExpressionEvaluator::evaluateLessEquals(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a <= b;
            
        }, "Type Mismatch: lessEquals requires two numeric operands");

    }

    Parser::Value ExpressionEvaluator::evaluateGreater(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a > b;
            
        }, "Type Mismatch: greaterThan requires two numeric operands");
    }

    Parser::Value ExpressionEvaluator::evaluateGreaterEquals(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a >= b;
            
        }, "NovellaScript Rutnime Error: operator '>=' requires two numeric operands");
    }

    Parser::Value ExpressionEvaluator::evaluateEquals(const Parser::Value& firstValue, const Parser::Value& secondValue){

        const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(firstValue.underlyingValue);
        const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(secondValue.underlyingValue);

        if(std::holds_alternative<bool>(primitiveFirst) && std::holds_alternative<bool>(primitiveSecond)){

            return applyPrimitiveOperation<bool, bool>(firstValue, secondValue,[](bool  a, bool b){

                return a == b;
                
            }, "NovellaScript Rutnime Error: operator 'is' requires the two compared values to be of the same type");

        }

        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<std::string>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, std::string>(firstValue, secondValue,[](const std::string&  a, const std::string& b){

                return a == b;
                
            }, "NovellaScript Rutnime Error: operator 'is' requires the two compared values to be of the same type");

        }

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a == b;
            
        }, "NovellaScript Rutnime Error: operator 'is' requires the two compared values to be of the same type");
    }

    Parser::Value ExpressionEvaluator::evaluateNotEquals(const Parser::Value& firstValue, const Parser::Value& secondValue){

        const auto& primitiveFirst = std::get<Parser::PrimitiveValue>(firstValue.underlyingValue);
        const auto& primitiveSecond = std::get<Parser::PrimitiveValue>(secondValue.underlyingValue);

        if(std::holds_alternative<bool>(primitiveFirst) && std::holds_alternative<bool>(primitiveSecond)){

            return applyPrimitiveOperation<bool, bool>(firstValue, secondValue,[](bool  a, bool b){

                return a != b;
                
            }, "NovellaScript Rutnime Error: operator 'not equals' requires the two compared values to be of the same type");

        }

        if(std::holds_alternative<std::string>(primitiveFirst) && std::holds_alternative<std::string>(primitiveSecond)){

            return applyPrimitiveOperation<std::string, std::string>(firstValue, secondValue,[](const std::string&  a, const std::string& b){

                return a != b;
                
            }, "NovellaScript Rutnime Error: operator 'not equals' requires the two compared values to be of the same type");

        }

        return applyPrimitiveOperation<double, double>(firstValue, secondValue,[](double a, double b){

            return a != b;
            
        }, "NovellaScript Rutnime Error: operator 'is not' requires the two compared values to be of the same type");

    }

    Parser::Value ExpressionEvaluator::evaluateAnd(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<bool, bool>(firstValue, secondValue,[](bool a, bool b){

            return a && b;
            
        }, "Type Mismatch: and requires two boolean operands");

    }

    Parser::Value ExpressionEvaluator::evaluateOr(const Parser::Value& firstValue, const Parser::Value& secondValue){

        return applyPrimitiveOperation<bool, bool>(firstValue, secondValue,[](bool a, bool b){

            return a || b;
            
        }, "Type Mismatch: or requires two boolean operands");
    }

    Parser::Value ExpressionEvaluator::evaluateBinaryExpression(const Parser::BinaryExpression& binaryExpression){

        Parser::Value firstValue = evaluate(*binaryExpression.left);
        Parser::Value secondValue = evaluate(*binaryExpression.right);

        if(binaryExpression.operation == Parser::Token::Type::Plus){

            return evaluateAddition(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Minus){

            return evaluateSubstraction(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Multiply){

            return evaluateMultiplication(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Divide){

            return evaluateDivision(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Modulo){

            return evaluateModulo(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Less){

            return evaluateLess(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::LessEquals){

            return evaluateLessEquals(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Greater){

            return evaluateGreater(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::GreaterEquals){

            return evaluateGreaterEquals(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Equals){

            return evaluateEquals(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::NotEquals){

            return evaluateNotEquals(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::And){

            return evaluateAnd(firstValue, secondValue);

        }else if(binaryExpression.operation == Parser::Token::Type::Or){

            return evaluateOr(firstValue, secondValue);
        }

        throw std::runtime_error("Invalid binary operation");
    }

    Parser::Value ExpressionEvaluator::evaluateIndexExpression(const Parser::IndexExpression& indexExpression){

        Parser::Value sourceValue = evaluate(*indexExpression.object);
        Parser::Value indexValue = evaluate(*indexExpression.index);

        double rawIndex = indexValue.get<double>();

        size_t index = static_cast<size_t>(rawIndex);

        if(!std::holds_alternative<std::vector<Parser::PrimitiveValue>>(sourceValue.underlyingValue)) throw std::runtime_error("Type Mismatch: index operations can only be applied to arrays");

        const auto& arrayElements = std::get<std::vector<Parser::PrimitiveValue>>(sourceValue.underlyingValue);

        if(index >= arrayElements.size()) throw std::runtime_error("NovellaScript Runtime Error: Array out of bounds exception, can't access index " + std::to_string(index) + " for array of size " + std::to_string(arrayElements.size()));

        Parser::Value result{};

        result.underlyingValue = arrayElements[index];
        
        return result;
    }

    Parser::Value ExpressionEvaluator::evaluateArrayExpression(const Parser::ArrayExpression& ArrayExpression){

        std::vector<Parser::PrimitiveValue> primitiveElements;

        primitiveElements.reserve(ArrayExpression.elements.size());

        for(const auto& element : ArrayExpression.elements){

            Parser::Value evaluatedElement = evaluate(element);

            if(!std::holds_alternative<Parser::PrimitiveValue>(evaluatedElement.underlyingValue)) throw std::runtime_error("NovellaScript does not support nested arrays");

            primitiveElements.push_back(std::get<Parser::PrimitiveValue>(evaluatedElement.underlyingValue));
        }

        Parser::Value result{};

        result.underlyingValue = primitiveElements;
        
        return result;
    }

    Parser::Value ExpressionEvaluator::evaluateLiteral(const Parser::LiteralExpression& literal){

        return literal.value;
    }   

    Parser::Value ExpressionEvaluator::evaluatePostFixExpression(const Parser::PostFixExpression& postFixExpression){

        if(auto variable = std::get_if<Parser::VariableExpression>(postFixExpression.operand.get())){

            std::string name = variable->name;

            Parser::Value oldOriginalValue = runtime.getVariable(name);

            Parser::Value modifiedValue{};

            if(postFixExpression.operation == Parser::Token::Type::Increment){

                modifiedValue = applyIncrement(oldOriginalValue);

            }else{

                modifiedValue = applyDecrement(oldOriginalValue);
            }

            runtime.setVariable(name, modifiedValue);

            return oldOriginalValue;

        }else if(auto indexExpression = std::get_if<Parser::IndexExpression>(postFixExpression.operand.get())){
        
            if(auto variable = std::get_if<Parser::VariableExpression>(indexExpression->object.get())){

                std::string arrayName = variable->name;

                Parser::Value entireArray = runtime.getVariable(arrayName);

                Parser::Value indexResponse = evaluate(*indexExpression->index);

                size_t targetIndex = static_cast<size_t>(indexResponse.get<double>());

                auto& elements = std::get<std::vector<Parser::PrimitiveValue>>(entireArray.underlyingValue);

                if(targetIndex >= elements.size()) throw std::runtime_error("NovellaScript Runtime Error: Index out of bounds");

                Parser::Value oldElementValue{};
                oldElementValue.underlyingValue = elements[targetIndex];

                Parser::Value newElementValue{};

                if(postFixExpression.operation == Parser::Token::Type::Increment){

                    newElementValue = applyIncrement(oldElementValue);

                }else if(postFixExpression.operation == Parser::Token::Type::Decrement){

                    newElementValue = applyDecrement(oldElementValue);
                }

                elements[targetIndex] = std::get<Parser::PrimitiveValue>(newElementValue.underlyingValue);

                runtime.setVariable(arrayName, entireArray);

                return oldElementValue;
            }        
        }

        throw std::runtime_error("Invalid postfix mutation expression target");
    }

    Parser::Value ExpressionEvaluator::evaluate(const Parser::Expression& expression){

        if(auto functionCall = std::get_if<Parser::FunctionCallExpression>(&expression)){
            
            return evaluateFunctionCall(*functionCall);

        }else if(auto literal = std::get_if<Parser::LiteralExpression>(&expression)){

            return literal->value;

        }else if(auto variable = std::get_if<Parser::VariableExpression>(&expression)){

            return evaluateVariable(*variable);

        }else if(auto unary = std::get_if<Parser::UnaryExpression>(&expression)){   

            return evaluateUnaryExpression(*unary);

        }else if(auto binary = std::get_if<Parser::BinaryExpression>(&expression)){

            return evaluateBinaryExpression(*binary);

        }else if(auto assignment = std::get_if<Parser::AssignmentExpression>(&expression)){
            
            return evaluateAssignmentExpression(*assignment);

        }else if(auto array = std::get_if<Parser::ArrayExpression>(&expression)){

            return evaluateArrayExpression(*array);

        }else if(auto index = std::get_if<Parser::IndexExpression>(&expression)){

            return evaluateIndexExpression(*index);

        }else if(auto postFix = std::get_if<Parser::PostFixExpression>(&expression)){

            return evaluatePostFixExpression(*postFix);
        }

        return Parser::Value{Parser::PrimitiveValue{std::monostate{}}};
    }

}