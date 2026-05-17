#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "../Input/Mouse.hpp"
#include "../Math/Vector2x.hpp"

namespace Novella::Attribute{

    struct Clickable{

        private:

        struct BindedAction{

        std::string name;
        nlohmann::json args;
        std::string target;
        };

        public:

        virtual ~Clickable() = default;

        const std::unordered_map<Input::Mouse, BindedAction>& getMouseBinds(){ return  mouseBinds;}
            
        virtual void addMouseBind(Input::Mouse, const std::string& name, const nlohmann::json& args, const std::string& target) = 0;
            
        virtual bool contains(const Math::Vector2i& mousePos) const = 0;
        
        protected:
        
        std::unordered_map<Input::Mouse, BindedAction> mouseBinds;
    };
}
