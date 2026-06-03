#pragma once
#include <string>
#include "Mouse.hpp"
#include "../Math/Vector2x.hpp"

namespace Novella::Input {

    struct ClickEvent{

        ClickEvent() = delete;
        
        ClickEvent(const std::string& objectID, Mouse::Button button, const Math::Vector2f& position)
            :
            objectID(objectID),
            button(button),
            position(position)
            {}
            
        std::string objectID;
        Mouse::Button button;
        Math::Vector2f position;

    };
}
