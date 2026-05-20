#pragma once
#include <string>
#include <nlohmann/json.hpp>
#include "../Input/Mouse.hpp"
#include "../Math/Vector2x.hpp"
#include "../Input/ActionCommand.hpp"

namespace Novella::Attribute{

    struct Clickable{

        protected:
        
        std::unordered_map<Input::Mouse::Button, Input::ActionCommand> mouseBinds;

        public:

        virtual ~Clickable() = default;

        const std::unordered_map<Input::Mouse::Button, Input::ActionCommand>& getMouseBinds() const{ return  mouseBinds;}
            
        virtual void addMouseBind(Input::Mouse::Button button, const std::string& name, const nlohmann::json& args, const std::string& target) = 0;
            
        virtual bool contains(const Math::Vector2f& mousePos) const = 0;
        
    };
}
