#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include <stdexcept>
#include <vector>
namespace Novella::NScript::Runtime{

    void FunctionExecutor::setRuntime(RuntimeEnvironment& runtime){

        this->runtime = &runtime;
    }

    void FunctionExecutor::setStatementEvaluator(StatementEvaluator& evaluator){

        this->statementEvaluator = &evaluator;
    }

    Parser::Value FunctionExecutor::call(const std::string& name, const std::vector<Parser::Value>& args){

        if(runtime->isNativeFunction(name)){
            
            return runtime->callNativeFunction(name, args);
        }

        if(runtime->isScriptFunction(name)){

            const auto& function = runtime->getFunction(name);

            statementEvaluator->execute(function.body);

        }else{

            throw std::runtime_error("Function not found: " + name);
        }

        return {};
    }
}