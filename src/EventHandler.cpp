#include "../Novella/Syntax/NovellaScript/Interpreter/EventHandler.hpp"
#include "../Novella/Syntax/NovellaScript/Interpreter/Converter.hpp"
#include "../Novella/Input/KeyEvent.hpp"
#include "../Novella/Input/ClickEvent.hpp"

namespace Novella::Syntax::NovellaScript{

    std::optional<Expression> EventHandler::getExpressionFromEvent(const Event& event){

        return std::visit([&](auto&& e) -> std::optional<Expression>{

            if(activeBindings.find(e.objectID) == activeBindings.end()) return std::nullopt;

            std::string inputString = Converter::getInputFromEvent(e);

            for(const auto& binding : activeBindings.at(e.objectID)){

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