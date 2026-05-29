#pragma once
#include <nlohmann/json_fwd.hpp>
#include <functional>
#include <unordered_map>
#include <stdexcept>
#include "../Commands/CommandContext.hpp"

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

    class CommandDispatcher{

        public:

        CommandDispatcher();
        
        CommandDispatcher(const CommandDispatcher&) = delete;

        CommandDispatcher& operator=(const CommandDispatcher&) = delete;

        CommandDispatcher(CommandDispatcher&&) = delete;
    
        CommandDispatcher& operator=(CommandDispatcher&&) = delete;

        bool registered(Alias alias) const;
                
        void trigger(const ActionCommand& command, CommandContext& context);

        private:
        
        using Func = std::function<void(CommandContext& context, const nlohmann::json& args)>;
        
        template<typename Func>

        void registerCommand(Alias commandAlias, Func function){

            commands.emplace(commandAlias, function);
        }

        std::unordered_map<Alias, Func> commands;
        
    };

}