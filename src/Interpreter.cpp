#include "../Novella/Syntax/NovellaScript/Interpreter.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include <variant>

namespace Novella::Syntax::NovellaScript{

    Interpreter::Interpreter(Input::CommandDispatcher& dispatcher)
        :
        dispatcher(dispatcher)
        {}

    Interpreter::RunTimeValue Interpreter::callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args){

        return RunTimeValue{};
    }
    
    void Interpreter::executeStatement(const Statement& statement){


    }

    std::string Interpreter::getFunctionName(const Expression* answer){

        //

        return std::string{};
    }

    Interpreter::RunTimeValue Interpreter::evaluateExpression(const Expression& expression){

        if(std::holds_alternative<FunctionCallExpression>(expression)){

            auto& call = std::get<FunctionCallExpression>(expression);

            std::string functionName = getFunctionName(call.answer.get());
        }

        return RunTimeValue{};
    }

    void Interpreter::resolveImports(){


    }
}