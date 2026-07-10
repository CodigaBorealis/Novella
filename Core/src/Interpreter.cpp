#include "../Novella/Scripting/Interpreter/Interpreter.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include "../Novella/Core/Engine.hpp"
#include "../Novella/Scripting/API/API.hpp"
#include <stdexcept>
namespace Novella::NScript::Runtime{

    Context& Interpreter::runtimeContext(){

        return runtime.context();
    }

    void Interpreter::run(){

        if(runtime.sceneChangeRequested()) return;

        if(runtime.isScriptFunction("main")){

            const auto& mainFunction = runtime.getFunction("main");

            statementEvaluator.execute(mainFunction.body);

        }else{

            throw std::runtime_error("No entry point 'main()' found in loaded scripts\n");
        }
    }

    void Interpreter::loadScript(const Parser::Script& script){

        runtime.registerData(script, expressionEvaluator);
    }

    void Interpreter::clear(){
        
        this->runtime.clear();
    }

    void Interpreter::initialize(Engine& engine){

        runtime.initializeContext(engine, *this);
        runtime.registerCoreFunctions();
    }

}