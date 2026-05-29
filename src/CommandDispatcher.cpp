#include "../Novella/Input/CommandDispatcher.hpp"
#include "../Novella/Input/ActionCommand.hpp"
#include <stdexcept>
#include <string>
#include "../Novella/Commands/CommandTable.hpp"
namespace Novella::Input{

    CommandDispatcher::CommandDispatcher(){

        for(const auto& command : commandTable){

            registerCommand(command.alias, command.function);
        }       
    }

    bool CommandDispatcher::registered(Alias alias) const{

        return commands.contains(alias);
    }
                
    void CommandDispatcher::trigger(const ActionCommand& command, CommandContext& context){
        
        auto it = commands.find(command.alias);

        if(it == commands.end()) throw std::runtime_error("Command not registered " + std::to_string(static_cast<int>(command.alias)));

        context.targetID = command.targetID;
        
        it->second(context, command.args);
    }

}