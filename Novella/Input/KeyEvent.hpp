#pragma once
#include <cstdint>
#include "KeyboardRaylib.hpp"

namespace Novella::Input {

    struct KeyEvent{

        KeyEvent() = delete;

        KeyEvent(uint64_t objectID, Keyboard::Key key)
            :
            objectID(objectID),
            key(key)
            {}
        
        uint64_t objectID;
        Keyboard::Key key;

    };
}
