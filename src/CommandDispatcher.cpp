#include "../Novella/Input/CommandDispatcher.hpp"
#include "../Novella/Commands/CommandTable.hpp"
#include "../Novella/Input/ClickEvent.hpp"
#include "../Novella/Input/KeyEvent.hpp"
#include <cstdint>
#include <stdexcept>
#include <string>
namespace Novella::Input{

    CommandDispatcher::CommandDispatcher(){

        for(const auto& command : commandTable){

            registerCommand(command.alias, command.function);
        }       
    }

    void CommandDispatcher::execute(uint64_t targetID, Alias alias, const nlohmann::json& args, CommandContext& context){

        auto it = commands.find(alias);

        if(it == commands.end()) throw std::runtime_error("Command not found\n ID:" + std::to_string(static_cast<unsigned int>(alias)));

        it->second(targetID, context, args);
    }

    void CommandDispatcher::dispatch(const KeyEvent& event, CommandContext& context){

        for(const auto& bind : keyBindings){

            if(bind.objectID == event.objectID && bind.key == event.key){

                execute(bind.objectID, bind.alias, bind.args, context);

                return;
            }
        }        
    }

    void CommandDispatcher::dispatch(const ClickEvent& event, CommandContext& context){

        for(const auto& bind : clickBindings){


            if(bind.objectID == event.objectID && bind.button == event.button){

                execute(bind.objectID,bind.alias, bind.args, context);

                return;
            }
        }        
    }

    void CommandDispatcher::addClickBinding(uint64_t objectID, Mouse::Button button, Alias commandAlias, const nlohmann::json& args){

        clickBindings.push_back({objectID, button, commandAlias, args});
    };

    void CommandDispatcher::addKeyBinding(uint64_t objectID, Keyboard::Key key, Alias commandAlias, const nlohmann::json& args){

        keyBindings.push_back({objectID, key, commandAlias, args});
    };
}