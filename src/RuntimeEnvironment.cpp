#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include <cstddef>
#include <stdexcept>
#include <variant>
#include "../Novella/Scripting/Interpreter/CoreInitializer.hpp"
#include "../Novella/Core/Engine.hpp"
#include <iostream>
#include <vector>

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

    void RuntimeEnvironment::printNativeFunctionAddresses() const{

        using ExpectedTargetType = Parser::Value(*)(Context&, const std::vector<Parser::Value>&);

        for(const auto& [name,func] : nativeFunctions){

            if(auto* const* targetPtr = func.target<ExpectedTargetType>()){

                void* address = reinterpret_cast<void*>(*targetPtr);

            }else{
            }
        }
    }

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
        CoreInitializer::registerInteraction(*this);
        CoreInitializer::registerLayout(*this);
        CoreInitializer::registerLogger(*this);
        CoreInitializer::registerRenderer(*this);
        CoreInitializer::registerScene(*this);
        CoreInitializer::registerWindow(*this);

    }

    void RuntimeEnvironment::registerData(const Parser::Script& script){

        for(const auto& definition : script.definitions){

            if(auto function = std::get_if<Parser::FunctionDefinition>(&definition)){

                    registerFunction(*function);
                }
            }
        }

    void RuntimeEnvironment::registerFunction(const Parser::FunctionDefinition& definition){

        auto it = scriptFunctions.find(definition.name);

        if(it != scriptFunctions.end()) throw std::runtime_error("A function with this name already exists '" + definition.name + "'");

        scriptFunctions.emplace(definition.name, definition);
    }

    void RuntimeEnvironment::createVariable(const std::string& name, const Parser::Value& value){

        auto it = variables.find(name);

        if(it != variables.end()) throw std::runtime_error("A variable with this name already exists '" + name + "'");

        variables.emplace(name, value);
    }

    Parser::Value& RuntimeEnvironment::getVariable(const std::string& name){

        auto it = variables.find(name);

        if(it == variables.end()) throw std::runtime_error("Cannot get undefined variable '" + name + "'");

        return it->second;
    }

    void RuntimeEnvironment::setVariable(const std::string& name, const Parser::Value& value){

        auto it = variables.find(name);

        if(it == variables.end()) throw std::runtime_error("Cannot set undefined variable '" + name + "'");

        it->second = value;
    }

    const Parser::FunctionDefinition& RuntimeEnvironment::getFunction(const std::string& name){

        auto it = scriptFunctions.find(name);

        if(it == scriptFunctions.end()) throw std::runtime_error("Cannot call undefined function '" + name + "'");

        return it->second;
    } 

    void RuntimeEnvironment::clear(){

        this->variables.clear();
        this->scriptFunctions.clear();
        this->persistentStorage.clear();
        this->callStack.clear();

    }
}