#pragma once
#include "../Script.hpp"
#include <unordered_map>
#include <variant>
#include <vector>
#include "../../Scene/SceneDefinition.hpp"
#include "../../../Commands/CommandTable.hpp"
#include "../ScriptFwd.hpp"
#include "EventHandler.hpp"
#include "ExpressionEvaluator.hpp"
#include "ModuleResolver.hpp"
#include "StatementExecutor.hpp"

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

        Interpreter() = default;

        void loadScript(const Scene::ScriptDefinition& definition);

        void interpretEvent(const EventHandler::Event& event);

        void clear();

        void runScripts();

        private:
        
        ModuleResolver moduleResolver;
        EventHandler eventHandler;
        ExpressionEvaluator expressionEvaluator;
        StatementExecutor statementEvaluator;

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        std::string getFunctionName(const Expression* answer);
        void executeStatements(const std::vector<Statement>& statements);
        void executeStatement(const Statement& statement);

        void run();
        void interpret(const Script& script);
        void execOnce(const Script& script);

        std::vector<Script> scripts;

        std::unordered_map<std::string, ModuleDefinition> loadedModules;
        
        std::unordered_map<std::string, std::unordered_map<std::string, RunTimeValue>> persistentStorage;
        std::unordered_map<std::string, RunTimeValue> localScope;
        
        Commands::CommandTable internalCommands;
    };

}