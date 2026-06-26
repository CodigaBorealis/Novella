#include "../Novella/Scripting/Interpreter/Interpreter.hpp"
#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"

namespace Novella::NScript::Runtime{

    void Interpreter::loadScript(const NScene::Parser::ScriptDefinition& definition){

        Parser::Script script = ScriptLoader::load(definition.path);

        moduleResolver.resolveImports(script);
        
        runtime.registerData(script);

        interpret(script);

    }

    void Interpreter::interpretEvent(const Event& event){

        if(auto expression = eventHandler.getExpressionFromEvent(event)){

            //statementEvaluator.execute((expression.value()));
        }
    }

    void Interpreter::interpret(const Parser::Script& script){
         
        statementEvaluator.execute(script);
    }

    void Interpreter::clear(){
        
        this->runtime.clear();
        this->eventHandler.clear();
    }

}