#include "../Novella/Input/CommandDispatcher.hpp"
#include <stdexcept>

namespace Novella::Input{

    Attribute::Object* CommandDispatcher::resolveTarget(Scene& scene, const std::string& target) const{

        auto* targetObject = scene.findObjectByID(target);

        if(targetObject != nullptr){

            return targetObject;

        }else{

            throw std::runtime_error("Object not found in the scene: " + target);
        }

    }

    bool CommandDispatcher::registered(const std::string& name) const{

        return commands.contains(name);
    }
                
    void CommandDispatcher::trigger(Scene& scene, const ActionCommand& command){
        
        auto* target = resolveTarget(scene, command.target);

        auto it = commands.find(command.name);

        if(it == commands.end()) throw std::runtime_error("This command is not registered in the scene: " + command.name);

        it->second(scene, *target, command.args);
    }

}