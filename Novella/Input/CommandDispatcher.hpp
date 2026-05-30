#pragma once
#include <cstdint>
#include <nlohmann/json_fwd.hpp>
#include <functional>
#include <unordered_map>
#include <vector>
#include "../Commands/CommandContext.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"

namespace Novella {

    enum class Alias : unsigned int;
}

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

        using Func = std::function<void(uint64_t, CommandContext& context, const nlohmann::json& args)>;


        public:

        CommandDispatcher();
        
        CommandDispatcher(const CommandDispatcher&) = delete;

        CommandDispatcher& operator=(const CommandDispatcher&) = delete;

        CommandDispatcher(CommandDispatcher&&) = delete;
    
        CommandDispatcher& operator=(CommandDispatcher&&) = delete;
        
        void execute(uint64_t targetID, Alias alias, const nlohmann::json& args, CommandContext& context);

        void dispatch(const KeyEvent& event, CommandContext& context);
        void dispatch(const ClickEvent& event, CommandContext& context);

        void addClickBinding(uint64_t objectID, Mouse::Button button, Alias commandAlias, const nlohmann::json& args);
        void addKeyBinding(uint64_t objectID, Keyboard::Key key, Alias commandAlias, const nlohmann::json& args);

        private:
        
        struct ClickBinding {

            ClickBinding() = delete;

            ClickBinding(uint64_t objectID, Mouse::Button button, Alias alias, const nlohmann::json& args)
                :
                objectID(objectID),
                button(button),
                alias(alias),
                args(args)
                {}

            uint64_t objectID;
            Mouse::Button button;

            Alias alias;
            nlohmann::json args;
        };

        struct KeyBinding{

            KeyBinding() = delete;

            KeyBinding(uint64_t objectID, Keyboard::Key key, Alias alias, const nlohmann::json& args)
                :
                objectID(objectID),
                key(key),
                alias(alias),
                args(args)
                {}
            uint64_t objectID;
            Keyboard::Key key;

            Alias alias;
            nlohmann::json args;
        };


        template<typename Func>

        void registerCommand(Alias commandAlias, Func function){

            commands.emplace(commandAlias, function);
        }
        
        std::unordered_map<Alias, Func> commands;

        std::vector<ClickBinding> clickBindings;
        std::vector<KeyBinding> keyBindings;


    };

}