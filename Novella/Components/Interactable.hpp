#pragma once
#include "../Input/Keyboard.hpp"
#include <unordered_map>
#include <string>
#include <nlohmann/json.hpp>

namespace Novella::Attribute{

    struct Interactable{
        
        private:

        struct BindedAction{

        std::string name;
        nlohmann::json args;
        std::string target;
        };

        public:
        virtual ~Interactable() = default;

        const std::unordered_map<Input::Keyboard, BindedAction>& getKeyboardBinds(){ return  keyboardBinds;}
            
        virtual void addKeyboardBind(Input::Keyboard, const std::string& name, const nlohmann::json& args, const std::string& target) = 0;

        protected:
        
        std::unordered_map<Input::Keyboard, BindedAction> keyboardBinds;
    };
}
