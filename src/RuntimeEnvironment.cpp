#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include <cstddef>
#include <stdexcept>
#include <variant>
#include "../Novella/Scripting/Interpreter/CoreInitializer.hpp"
#include "../Novella/Core/Engine.hpp"
#include <vector>
#include "../Novella/Scripting/Interpreter/ExpressionEvaluator.hpp"

namespace Novella::NScript::Runtime{

    size_t RuntimeEnvironment::loadedFunctions() const{

        return scriptFunctions.size();
    }
    
    Parser::Value RuntimeEnvironment::callNativeFunction(const std::string& name, const std::vector<Parser::Value>& args){

        auto it = nativeFunctions.find(name);

        if(it == nativeFunctions.end()) throw std::runtime_error("No such function in the API: " + name);

        return it->second(runtimeContext, args);
    }

    bool RuntimeEnvironment::isNativeFunction(const std::string& name) const{

        return nativeFunctions.contains(name);
    }

    bool RuntimeEnvironment::isScriptFunction(const std::string& name) const{

        return scriptFunctions.contains(name);
    } 
/*
    void RuntimeEnvironment::printNativeFunctionAddresses() const{

        using ExpectedTargetType = Parser::Value(*)(Context&, const std::vector<Parser::Value>&);

        for(const auto& [name,func] : nativeFunctions){

            if(auto* const* targetPtr = func.target<ExpectedTargetType>()){

                void* address = reinterpret_cast<void*>(*targetPtr);

            }else{
            }
        }
    }
*/
    void RuntimeEnvironment::initializeContext(Engine& engine){

        this->runtimeContext.audio = &engine.audio();
        this->runtimeContext.input = &engine.input();
        this->runtimeContext.layout = &engine.layout();
        this->runtimeContext.logger = &engine.logger();
        this->runtimeContext.renderer = &engine.renderer();
        this->runtimeContext.scene = &engine.scene();
        this->runtimeContext.window = &engine.window();
        this->runtimeContext.projectRoot = engine.projectRoot();
    }

    void RuntimeEnvironment::registerCoreFunctions(){

        CoreInitializer::registerAudio(*this);
        CoreInitializer::registerLogger(*this);
        CoreInitializer::registerRenderer(*this);
        CoreInitializer::registerScene(*this);
        CoreInitializer::registerWindow(*this);
        CoreInitializer::registerMath(*this);
        CoreInitializer::registerString(*this);
        CoreInitializer::registerFilesystem(*this);
        CoreInitializer::registerInput(*this);
        CoreInitializer::registerRandomModule(*this);
        CoreInitializer::registerTransform(*this);
        CoreInitializer::registerSpriteModule(*this);
        CoreInitializer::registerTextModule(*this);
        CoreInitializer::registerUIModule(*this);
        CoreInitializer::registerObjectModule(*this);
        CoreInitializer::registerOS(*this);

    }

    void RuntimeEnvironment::registerData(const Parser::Script& script, ExpressionEvaluator& expressionEvaluator){

        for(const auto& definition : script.definitions){

            if(auto function = std::get_if<Parser::FunctionDefinition>(&definition)){

                registerFunction(*function);

            }else if(auto variable = std::get_if<Parser::VariableStatement>(&definition)){

                createVariable(variable->name, expressionEvaluator.evaluate(variable->value));
            }
        }
    }

    void RuntimeEnvironment::registerFunction(const Parser::FunctionDefinition& definition){

        auto it = scriptFunctions.find(definition.name);

        if(it != scriptFunctions.end()) throw std::runtime_error("NovellaScript Runtime Error: A function with this name already exists '" + definition.name + "'");

        scriptFunctions.emplace(definition.name, definition);
    }

    void RuntimeEnvironment::createVariable(const std::string& name, const Parser::Value& value){

        if(!callStack.empty()){

            callStack.back().locals.back()[name] = value;

        }else{

            auto it = globalVariables.find(name);

            if(it != globalVariables.end()) throw std::runtime_error("NovellaScript Runtime Error: A global variable with this name already exists '" + name + "'");

            globalVariables.emplace(name, value);
        }
    }

    Parser::Value& RuntimeEnvironment::getVariable(const std::string& name){

        if(!callStack.empty()){

            auto& scopeStack = callStack.back().locals;

            for(auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it){

                auto varIt = it->find(name);

                if(varIt != it->end()) return varIt->second;
            }
        }

        auto globalIterator = globalVariables.find(name);

        if(globalIterator != globalVariables.end()) return globalIterator->second;

        throw std::runtime_error("NovellaScript Runtime Error: Cannot get undefined variable '" + name + "'");
    }

    void RuntimeEnvironment::setVariable(const std::string& name, const Parser::Value& value){

        if(!callStack.empty()){

            auto& scopeStack = callStack.back().locals;

            for(auto it = scopeStack.rbegin(); it != scopeStack.rend(); ++it){

                auto varIt = it->find(name);

                if(varIt != it->end()){

                    varIt->second = value;

                    return;
                }
            }
        }

        auto globalIterator = globalVariables.find(name);

        if(globalIterator != globalVariables.end()){

            globalIterator->second = value;

            return;
        }

        throw std::runtime_error("NovellaScript Runtime Error: Cannot set undefined variable '" + name + "'");
    }

    const Parser::FunctionDefinition& RuntimeEnvironment::getFunction(const std::string& name){

        auto it = scriptFunctions.find(name);

        if(it == scriptFunctions.end()) throw std::runtime_error("NovellaScript Runtime Error: Cannot call undefined function '" + name + "'");

        return it->second;
    } 

    void RuntimeEnvironment::clear(){

        this->globalVariables.clear();
        this->scriptFunctions.clear();
        this->callStack.clear();

    }

    std::vector<RuntimeEnvironment::CallFrame>& RuntimeEnvironment::functionCalls(){

        return callStack;
    }

    size_t RuntimeEnvironment::callStackLimit() const{

        return MAX_CALL_STACK;
    }

    bool RuntimeEnvironment::isGlobal(const std::string& name) const{

        return globalVariables.contains(name);
    }
/*
    void RuntimeEnvironment::printVariables() const{

        for(const auto& [variable, value] : variables){

            std::cout << "Variable name: " << variable;
        }
    }*/

    void RuntimeEnvironment::pushScope(){

        if(!callStack.empty()) callStack.back().locals.emplace_back();
    }

    void RuntimeEnvironment::popScope(){

        if(!callStack.empty() && !callStack.back().locals.empty()) callStack.back().locals.pop_back();
    }
}