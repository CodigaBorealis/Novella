#include "../Novella/Scripting/Interpreter/EventHandler.hpp"
#include "../Novella/Scripting/Interpreter/Converter.hpp"

namespace Novella::NScript::Runtime{

    std::optional<Parser::Expression> EventHandler::getExpressionFromEvent(const Event& event){

        return std::visit([&](auto&& e) -> std::optional<Parser::Expression>{

            if(activeBindings.find(e.objectHandle) == activeBindings.end()) return std::nullopt;

            std::string inputString = Converter::getInputFromEvent(e);

            for(const auto& binding : activeBindings.at(e.objectHandle)){

                if(binding.triggerName == inputString){

                    return *binding.callbackAction;
                }
            }

            return std::nullopt;
        }, event);

    }

    void EventHandler::clear(){

        this->activeBindings.clear();
    }

}