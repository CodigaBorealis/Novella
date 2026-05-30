#pragma once
#include <cstdint>
#include "Mouse.hpp"
#include "MouseRaylib.hpp"
#include "../Math/Vector2x.hpp"

namespace Novella::Input {

    struct ClickEvent{

        ClickEvent() = delete;
        
        ClickEvent(uint64_t objectID, Mouse::Button button, const Math::Vector2f& position)
            :
            objectID(objectID),
            button(button),
            position(position)
            {}
            
        uint64_t objectID;
        Mouse::Button button;
        Math::Vector2f position;

    };
}
