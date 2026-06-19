#pragma once
#include "../Script.hpp"
#include <variant>
#include <vector>
#include "../../Scene/SceneDefinition.hpp"
#include "../ScriptFwd.hpp"
#include "EventHandler.hpp"
#include "ModuleResolver.hpp"
#include "RuntimeEnvironment.hpp"
#include "StatementEvaluator.hpp"

namespace Novella::Input::Keyboard{

    enum class Key;
}
namespace Novella::Input::Mouse{

    enum class Button;
}

namespace Novella::Input{

    class InteractionSystem;

    struct KeyEvent;

    struct ClickEvent;
}

namespace Novella::Syntax::NovellaScript{

    class Interpreter{

        struct RuntimeBinding{
            
            std::string triggerName;
            std::shared_ptr<FunctionCallExpression> callbackAction;
        };

        public:
        
        using RunTimeValue = std::variant<std::monostate, double, bool, std::string, char, std::vector<Expression>>;

        Interpreter()
            :
            statementEvaluator(runtime),
            runtime(statementEvaluator)
            {}

        void loadScript(const Scene::ScriptDefinition& definition);

        void interpretEvent(const EventHandler::Event& event);

        void clear();

        private:
        
        RuntimeEnvironment runtime;
        ModuleResolver moduleResolver;
        StatementEvaluator statementEvaluator;
        EventHandler eventHandler;

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        std::string getFunctionName(const Expression* answer);
        void executeStatements(const std::vector<Statement>& statements);
        void executeStatement(const Statement& statement);

        void interpret(const Script& script);
    };

}