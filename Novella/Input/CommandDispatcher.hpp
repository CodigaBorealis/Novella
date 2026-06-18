#pragma once
#include <nlohmann/json_fwd.hpp>
#include <functional>
#include <string>
#include <unordered_map>
#include <vector>
#include "../Commands/CommandContext.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Novella::Attribute{

    class Object;
}

namespace Novella::Input{

    class ActionCommand;
}

namespace Novella{

    class Scene;
}

namespace Novella::Input{

    class KeyEvent;
    class ClickEvent;

}

namespace Novella::Input{

    class CommandDispatcher{

        using Func = std::function<void(const std::string&, CommandContext& context, const nlohmann::json& args)>;


        public:

        CommandDispatcher();
        
        CommandDispatcher(const CommandDispatcher&) = delete;

        CommandDispatcher& operator=(const CommandDispatcher&) = delete;

        CommandDispatcher(CommandDispatcher&&) = delete;
    
        CommandDispatcher& operator=(CommandDispatcher&&) = delete;
        
        void execute(const std::string& targetID, const std::string&  alias, const nlohmann::json& args, CommandContext& context);

        void dispatch(const KeyEvent& event, CommandContext& context);
        void dispatch(const ClickEvent& event, CommandContext& context);

        void addClickBinding(const std::string& objectID, Mouse::Button button, const std::string& commandAlias, const nlohmann::json& args);
        void addKeyBinding(const std::string& objectID, Keyboard::Key key, const std::string& commandAlias, const nlohmann::json& args);

        void clear();
        
        private:
        
        struct ClickBinding {

            ClickBinding() = delete;

            ClickBinding(const std::string&  objectID, Mouse::Button button, const std::string&  alias, const nlohmann::json& args)
                :
                objectID(objectID),
                button(button),
                alias(alias),
                args(args)
                {}

            std::string objectID;
            Mouse::Button button;

            std::string alias;
            nlohmann::json args;
        };

        struct KeyBinding{

            KeyBinding() = delete;

            KeyBinding(const std::string&  objectID, Keyboard::Key key, const std::string&  alias, const nlohmann::json& args)
                :
                objectID(objectID),
                key(key),
                alias(alias),
                args(args)
                {}

            std::string objectID;
            Keyboard::Key key;

            std::string alias;
            nlohmann::json args;
        };


        template<typename Func>

        void registerCommand(const std::string& commandAlias, Func function){

            commands.emplace(commandAlias, function);
        }
        
        std::unordered_map<std::string, Func> commands;

        std::vector<ClickBinding> clickBindings;
        std::vector<KeyBinding> keyBindings;

    };

}