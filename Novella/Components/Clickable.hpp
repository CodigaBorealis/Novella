#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "../Input/Mouse.hpp"
#include "../Math/Vector2x.hpp"

namespace Novella::Attribute{

    struct Clickable{

        protected:

        struct BindedAction{

        std::string name;
        nlohmann::json args;
        std::string target;
        };
        
        std::unordered_map<Input::Mouse, BindedAction> mouseBinds;

        public:

        virtual ~Clickable() = default;

        const std::unordered_map<Input::Mouse, BindedAction>& getMouseBinds(){ return  mouseBinds;}
            
        virtual void addMouseBind(Input::Mouse, const std::string& name, const nlohmann::json& args, const std::string& target) = 0;
            
        virtual bool contains(const Math::Vector2f& mousePos) const = 0;
        
    };
}
