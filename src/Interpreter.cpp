#include "../Novella/Syntax/NovellaScript/Interpreter/Interpreter.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include "../Novella/Input/InteractionSystem.hpp"
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <variant>
#include <nlohmann/json.hpp>
#include "../Novella/Syntax/NovellaScript/Interpreter/ScriptLoader.hpp"
#include <iostream>
#include <vector>

namespace Novella::Syntax::NovellaScript{

    void Interpreter::loadScript(const Scene::ScriptDefinition& definition){

        Script script = ScriptLoader::load(definition.path);

        this->scripts.push_back(script);

        interpret(script);

    }

    void Interpreter::run(){

        for(auto& script : scripts){

            interpret(script);
        }
    }

    void Interpreter::interpretEvent(const EventHandler::Event& event){

        if(auto expression = eventHandler.getExpressionFromEvent(event)){

            expressionEvaluator.evaluate(expression.value());
        }
    }

    void Interpreter::execOnce(const Script& script){

        auto execOnce = statementEvaluator.evaluateExecOnce(script);

        for(const auto& statement :  execOnce){

            expressionEvaluator.evaluate(statement);

        }
    }

    void Interpreter::interpret(const Script& script){

        auto body = statementEvaluator.evaluateDefinitions(script);
        
    }

    void Interpreter::clear(){
        
        this->scripts.clear();        
        this->persistentStorage.clear();
        this->localScope.clear();
        this->eventHandler.clear();
    }

}