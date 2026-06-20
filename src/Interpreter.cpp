#include "../Novella/Syntax/NovellaScript/Interpreter/Interpreter.hpp"
#include "../Novella/Input/InteractionSystem.hpp"
#include <optional>
#include <nlohmann/json.hpp>
#include "../Novella/Syntax/NovellaScript/Interpreter/ScriptLoader.hpp"
#include <variant>
#include <iostream>
namespace Novella::Syntax::NovellaScript{

    void Interpreter::loadScript(const Scene::ScriptDefinition& definition){

        Script script = ScriptLoader::load(definition.path);

        moduleResolver.resolveImports(script);
        
        runtime.registerData(script);

        interpret(script);

    }

    void Interpreter::interpretEvent(const EventHandler::Event& event){

        if(auto expression = eventHandler.getExpressionFromEvent(event)){

            //statementEvaluator.execute((expression.value()));
        }
    }

    void Interpreter::interpret(const Script& script){
         
        std::cout << "REACHED INTERPRETER\n";

        statementEvaluator.execute(script);
    }

    void Interpreter::clear(){
        
        this->runtime.clear();
        this->eventHandler.clear();
    }

}