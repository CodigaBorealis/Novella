#pragma once
#include "../Input/Keyboard.hpp"
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>
#include "../Input/ActionCommand.hpp"

namespace Novella::Attribute{

    struct Interactable{

        protected:

        std::unordered_map<Input::Keyboard::Key, Input::ActionCommand> keyboardBinds;
        public:
        virtual ~Interactable() = default;

        const std::unordered_map<Input::Keyboard::Key, Input::ActionCommand>& getKeyboardBinds() const{ return  keyboardBinds;}
            
        virtual void addKeyboardBind(Input::Keyboard::Key, const std::string& name, const nlohmann::json& args, const std::string& target) = 0;

       
    };
}
