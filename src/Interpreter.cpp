#include "../Novella/Scripting/Interpreter/Interpreter.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include "../Novella/Core/Engine.hpp"
#include "../Novella/Scripting/API/API.hpp"
#include <iostream>
namespace Novella::NScript::Runtime{

    void Interpreter::loadScript(const NScene::Parser::ScriptDefinition& definition){

        Parser::Script script = ScriptLoader::load(definition.path);
        
        runtime.registerData(script);

    }

    void Interpreter::interpretEvent(const Event& event){

        if(auto expression = eventHandler.getExpressionFromEvent(event)){

            statementEvaluator.execute(expression.value());
        }
    }

    void Interpreter::clear(){
        
        this->runtime.clear();
        this->eventHandler.clear();
    }

    void Interpreter::initialize(Engine& engine){

        std::cout << "CALLED INITIALIZE\n";
        runtime.initializeContext(engine);
        std::cout << "FINISHED INITIALIZING THE CONTEXT\n";
        runtime.registerCoreFunctions();
        std::cout << "LOADED ENGINE API\n";
        runtime.printNativeFunctionAddresses();

    }

}