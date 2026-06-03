#pragma once
#include <cstdint>
#include "Keyboard.hpp"
#include <string>
namespace Novella::Input {

    struct KeyEvent{

        KeyEvent() = delete;

        KeyEvent(const std::string& objectID, Keyboard::Key key)
            :
            objectID(objectID),
            key(key)
            {}
        
        std::string objectID;
        Keyboard::Key key;

    };
}
