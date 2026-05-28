#include "../Novella/Input/CommandDispatcher.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Input/ActionCommand.hpp"
#include <stdexcept>

namespace Novella::Input{

    Attribute::Object* CommandDispatcher::resolveTarget(Scene& scene, unsigned int targetID) const{

        auto* targetObject = scene.findObjectByID(targetID);

        if(targetObject != nullptr){

            return targetObject;

        }else{

            throw std::runtime_error("Object not found in the scene: " + std::to_string(targetID));
        }

    }

    bool CommandDispatcher::registered(const std::string& name) const{

        return commands.contains(name);
    }
                
    void CommandDispatcher::trigger(Scene& scene, const ActionCommand& command){
        
        auto* target = resolveTarget(scene, static_cast<uint64_t>(command.target));

        auto it = commands.find(command.name);

        if(it == commands.end()) throw std::runtime_error("This command is not registered in the scene: " + command.name);

        it->second(scene, *target, command.args);
    }

}