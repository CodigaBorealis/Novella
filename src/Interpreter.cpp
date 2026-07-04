#include "../Novella/Scripting/Interpreter/Interpreter.hpp"
#include "../Novella/Scripting/Parser/Definition.hpp"
#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Scripting/Interpreter/ScriptLoader.hpp"
#include "../Novella/Scripting/Parser/Script.hpp"
#include "../Novella/Scene/Parser/SceneDefinition.hpp"
#include "../Novella/Core/Engine.hpp"
#include "../Novella/Scripting/API/API.hpp"
#include <iostream>
#include <stdexcept>
namespace Novella::NScript::Runtime{

    void Interpreter::run(){

        static bool firstRun = true;

        if(runtime.isScriptFunction("main")){

            if(firstRun) std::cout << "Found main entrypoint\n";

            const auto& mainFunction = runtime.getFunction("main");

            statementEvaluator.execute(mainFunction.body);

            firstRun = false;
        }else{

            throw std::runtime_error("No entry point 'main()' found in loaded scripts\n");
        }
    }

    void Interpreter::loadScript(const Parser::Script& script){

        runtime.registerData(script);

        std::cout << "TOTAL FUNCTIONS LOADED FROM SCRIPTS: " << runtime.loadedFunctions() << "\n";

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