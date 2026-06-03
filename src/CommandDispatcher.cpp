#include "../Novella/Input/CommandDispatcher.hpp"
#include "../Novella/Commands/CommandTable.hpp"
#include "../Novella/Input/ClickEvent.hpp"
#include "../Novella/Input/KeyEvent.hpp"
#include <cstddef>
#include <stdexcept>
#include <string>

namespace Novella::Input{

    CommandDispatcher::CommandDispatcher(){

        for(const auto& command : commandTable){

            registerCommand(command.first, command.second);
        }       
    }

    void CommandDispatcher::execute(const std::string& targetID, const std::string& alias, const nlohmann::json& args, CommandContext& context){

        auto it = commands.find(alias);

        if(it == commands.end()) throw std::runtime_error("Command not found: '" + alias + "'");

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

    void CommandDispatcher::addClickBinding(const std::string& objectID, Mouse::Button button, const std::string& commandAlias, const nlohmann::json& args){

        clickBindings.push_back({objectID, button, commandAlias, args});

    };

    void CommandDispatcher::addKeyBinding(const std::string& objectID, Keyboard::Key key, const std::string& commandAlias, const nlohmann::json& args){

        keyBindings.push_back({objectID, key, commandAlias, args});

    };

}