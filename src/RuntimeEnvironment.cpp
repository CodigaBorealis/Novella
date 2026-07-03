#include "../Novella/Scripting/Interpreter/RuntimeEnvironment.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include <stdexcept>
#include <variant>

namespace Novella::NScript::Runtime{

    void RuntimeEnvironment::registerData(const Parser::Script& script){

        for(const auto& definition : script.definitions){

            if(std::holds_alternative<Parser::ModuleDefinition>(definition)){

                auto& module = std::get<Parser::ModuleDefinition>(definition);

                for(const auto& function : module.functions){

                    registerFunction(function);
                }
            }
        }
    }

    void RuntimeEnvironment::registerFunction(const Parser::FunctionDefinition& definition){

        auto it = functions.find(definition.name);

        if(it != functions.end()) throw std::runtime_error("A function with this name already exists '" + definition.name + "'");

        functions.emplace(definition.name, definition);
    }

    void RuntimeEnvironment::createVariable(const std::string& name, const Parser::Value& value){

        auto it = variables.find(name);

        if(it != variables.end()) throw std::runtime_error("A variable with this name already exists '" + name + "'");

        variables.emplace(name, value);
    }

    Parser::Value RuntimeEnvironment::getVariable(const std::string& name) const{

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

        auto it = functions.find(name);

        if(it == functions.end()) throw std::runtime_error("Cannot call undefined function '" + name + "'");

        return it->second;
    }

    void RuntimeEnvironment::clear(){

        this->variables.clear();
        this->functions.clear();
        this->loadedModules.clear();
        this->persistentStorage.clear();
        this->callStack.clear();

    }
}