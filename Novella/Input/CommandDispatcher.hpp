#pragma once
#include <nlohmann/json_fwd.hpp>
#include <string>
#include <functional>
#include <unordered_map>
#include <stdexcept>

namespace Novella::Input{

    enum class Target : unsigned int;

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

        CommandDispatcher() = default;
        
        CommandDispatcher(const CommandDispatcher&) = delete;

        CommandDispatcher& operator=(const CommandDispatcher&) = delete;

        CommandDispatcher(CommandDispatcher&&) = delete;
    
        CommandDispatcher& operator=(CommandDispatcher&&) = delete;

        bool registered(const std::string& name) const;
                
        void trigger(Scene& scene, const ActionCommand& command);

        private:
        
        using Func = std::function<void(Scene& scene, Attribute::Object&, const nlohmann::json&)>;

        Attribute::Object* resolveTarget(Scene& scene, unsigned int targetID) const;
        
        template<typename T>

        struct CommandTraits;

        template<typename T>

        
        struct CommandTraits<void(*)(T&, const nlohmann::json&)>{

            using ObjectType = T;
        };

        template<typename Func>

        void registerCommand(const std::string& name, Func function){

            commands.emplace(name, bindCommand(function));
        }

        template<typename Func> 

        auto bindCommand(Func function){

            using T = typename CommandTraits<Func>::ObjectType;
            
            return [function](Attribute::Object& object, const nlohmann::json& args){

                if(auto* casted = dynamic_cast<T*>(&object)){

                    function(*casted, args);

                }else{

                    throw std::runtime_error("Moon::System::CommandDispatcher:bindCommand: Invalid object type for command");
                }
            };
        }

        std::unordered_map<std::string, Func> commands;
        
    };

}