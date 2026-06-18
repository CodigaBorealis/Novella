#pragma once
#include "Script.hpp"
#include <unordered_map>
#include <variant>
#include <vector>
#include "Definition.hpp"//Don't remove this
#include "../Scene/SceneDefinition.hpp"
#include "../../Commands/CommandTable.hpp"

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
        
        using Event = std::variant<Input::KeyEvent, Input::ClickEvent>;

        using RunTimeValue = std::variant<std::monostate, double, bool, std::string, char, std::vector<Expression>>;

        Interpreter() = default;

        void loadScript(const Scene::ScriptDefinition& definition);

        void interpretEvent(const Event& event, CommandContext& context);
        void clear();

        private:
        
        void callInternalCommand(const std::string& name, const std::string& target, CommandContext& context, const nlohmann::json& args);

        RunTimeValue callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args = {});

        std::string convertButtonToString(Input::Mouse::Button button);
        std::string convertKeyToString(Input::Keyboard::Key key);

        std::string getFunctionName(const Expression* answer);
        void executeStatement(const Statement& statement);

        RunTimeValue evaluateExpression(const Expression& expression, CommandContext& context);

        void resolveImports();

        std::vector<Script> scripts;

        std::unordered_map<std::string, std::unordered_map<std::string, RunTimeValue>> persistentStorage;
        std::unordered_map<std::string, RunTimeValue> localScope;
        std::unordered_map<std::string, std::vector<RuntimeBinding>> activeBindings;   
        
        Commands::CommandTable internalCommands;
    };

}