#pragma once
#include <stdexcept>
#include <string>

namespace Novella{

    enum class Button{

        #define X(name, raylib) name,
        #include "MouseButtons.hpp"
        #undef X
    };
    
    enum class Key{

        #define X(name, raylib) name,
        #include "Keys.hpp"
        #undef X

    };

    static constexpr Key getKey(const std::string& stringRepresentation){

    if(stringRepresentation.size() == 1 && stringRepresentation[0] >= 'A' && stringRepresentation[0] <= 'Z'){

            return static_cast<Key>(static_cast<int>(Key::A) + stringRepresentation[0] - 'A');
        }

        if(stringRepresentation == "0") return Key::Num0;

        if(stringRepresentation == "1") return Key::Num1;

        if(stringRepresentation == "2") return Key::Num2;

        if(stringRepresentation == "3") return Key::Num3;

        if(stringRepresentation == "4") return Key::Num4;

        if(stringRepresentation == "5") return Key::Num5;

        if(stringRepresentation == "6") return Key::Num6;

        if(stringRepresentation == "7") return Key::Num7;

        if(stringRepresentation == "8") return Key::Num8;

        if(stringRepresentation == "9") return Key::Num9;

        if(stringRepresentation == "ESCAPE") return Key::Escape;

        if(stringRepresentation == "SPACE") return Key::Space;

        if(stringRepresentation == "ENTER") return Key::Enter;

        if(stringRepresentation == "BACKSPACE") return Key::Backspace;

        if(stringRepresentation == "TAB") return Key::Tab;

        if(stringRepresentation == "LEFT") return Key::Left;

        if(stringRepresentation == "RIGHT") return Key::Right;

        if(stringRepresentation == "UP") return Key::Up;

        if(stringRepresentation == "DOWN") return Key::Down;

        if(stringRepresentation == "LSHIFT") return Key::LShift;

        if(stringRepresentation == "RSHIFT") return Key::RShift;
        
        if(stringRepresentation == "LCONTROL") return Key::LControl;

        if(stringRepresentation == "RCONTROL") return Key::RControl;

        if(stringRepresentation == "LALT") return Key::LAlt;

        if(stringRepresentation == "RALT") return Key::RAlt;

        throw std::runtime_error("Unknown key: " + stringRepresentation);

    }

    static constexpr Button getButton(const std::string& stringRepresentation){

        if(stringRepresentation == "LEFT") return Button::Left;
        
        if(stringRepresentation == "RIGHT") return Button::Right;

        if(stringRepresentation == "MIDDLE") return Button::Middle;

        if(stringRepresentation == "SIDE") return Button::Side;

        if(stringRepresentation == "EXTRA") return Button::Extra;

        if(stringRepresentation == "FORWARD") return Button::Forward;

        if(stringRepresentation == "BACK") return Button::Back;

        throw std::runtime_error("Unknown button: " + stringRepresentation);
    }

}