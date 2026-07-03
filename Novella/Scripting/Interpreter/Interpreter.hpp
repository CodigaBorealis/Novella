#pragma once
#include "../Parser/Script.hpp"
#include <variant>
#include <vector>
#include "../Parser/ScriptFwd.hpp"
#include "EventHandler.hpp"
#include "ModuleResolver.hpp"
#include "RuntimeEnvironment.hpp"
#include "../Parser/StatementEvaluator.hpp"
#include "../../Systems/Input/InputEvent.hpp"

namespace Novella::Input{

    enum class Key;
}
namespace Novella::Input::Mouse{

    enum class Button;
}

namespace Novella{

    class InteractionSystem;

    struct KeyboardEvent;

    struct MouseEvent;
}

namespace Novella::NScene::Parser{

    struct ScriptDefinition;
}

namespace Novella::NScript::Runtime{

    class Interpreter{
        
        struct RuntimeBinding{
            
            std::string triggerName;
            std::shared_ptr<Parser::FunctionCallExpression> callbackAction;
        };

        public:
        
        using RunTimeValue = std::variant<std::monostate, double, bool, std::string, char, std::vector<Parser::Expression>>;

        Interpreter()
            :
            statementEvaluator(runtime)
            {}

        void loadScript(const NScene::Parser::ScriptDefinition& definition);

        void interpretEvent(const Event& event);

        void clear();

        private:
        
        RuntimeEnvironment runtime;
        ModuleResolver moduleResolver;
        Parser::StatementEvaluator statementEvaluator;
        EventHandler eventHandler;

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        std::string getFunctionName(const Parser::Expression* answer);
        void executeStatements(const std::vector<Parser::Statement>& statements);
        void executeStatement(const Parser::Statement& statement);

        void interpret(const Parser::Script& script);
    };

}