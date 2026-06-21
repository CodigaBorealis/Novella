#pragma once
#include "InputTypes.hpp"
#include "../../Core/Math/Vector2x.hpp"
#include <cstdint>
#include <variant>

namespace Novella{

    struct MouseEvent{

        MouseEvent() = delete;
        
        MouseEvent(uint64_t objectHandle, Button button, const Vector2f& position)
            :
            objectHandle(objectHandle),
            button(button),
            position(position)
            {}
            
        uint64_t objectHandle;
        Button button;
        Vector2f position;

    };

    struct KeyboardEvent{

        KeyboardEvent() = delete;

        KeyboardEvent(uint64_t objectHandle, Key key)
            :
            objectHandle(objectHandle),
            key(key)
            {}
        
        uint64_t objectHandle;
        Key key;

    };

    using Event = std::variant<MouseEvent, KeyboardEvent>;
}
