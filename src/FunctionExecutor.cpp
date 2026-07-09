#include "../Novella/Scripting/Interpreter/FunctionExecutor.hpp"
#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Interpreter/ReturnException.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>
#include <vector>
namespace Novella::NScript::Runtime{

    FunctionExecutor::CallFrameGuard::CallFrameGuard(RuntimeEnvironment* runtime, const std::string& name)
    :runtime(runtime){

        runtime->functionCalls().push_back({name});
        runtime->pushScope();
    }

    FunctionExecutor::CallFrameGuard::~CallFrameGuard(){

        if(!runtime->functionCalls().empty()){

            runtime->functionCalls().pop_back();
        }
    }

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
            
        if(runtime->functionCalls().size() >= runtime->callStackLimit()) throw std::runtime_error("NovellaScript Runtime Error: Infinite recursion detected, last function called: " + runtime->functionCalls().back().functionName);

            CallFrameGuard guard(runtime, name);

            const auto& function = runtime->getFunction(name);

            const auto& params = function.parameters;

            if(params.size() != args.size()) throw std::runtime_error("NovellaScript Runtime Error: Argument mismatch for function '" + function.name + "' expected " + std::to_string(params.size()) + " got: " + std::to_string(args.size()));
            
            if(!params.empty()){

                for(size_t x = 0; x < params.size(); x ++){

                    runtime->createVariable(params[x], args[x]);
                }
            }

            try{    

                statementEvaluator->execute(function.body);

            }catch(const ReturnException& returnSignal){

                return returnSignal.value;
            }

            return {};
        }

        throw std::runtime_error("NovellaScript Runtime Error: Function not found: '" + name + "'");
        
    }
}