#pragma once
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

        if(stringRepresentation == "Num0") return Key::Num0;

        if(stringRepresentation == "Num1") return Key::Num1;

        if(stringRepresentation == "Num2") return Key::Num2;

        if(stringRepresentation == "Num3") return Key::Num3;

        if(stringRepresentation == "Num4") return Key::Num4;

        if(stringRepresentation == "Num5") return Key::Num5;

        if(stringRepresentation == "Num6") return Key::Num6;

        if(stringRepresentation == "Num7") return Key::Num7;

        if(stringRepresentation == "Num8") return Key::Num8;

        if(stringRepresentation == "Num9") return Key::Num9;

        if(stringRepresentation == "Escape") return Key::Escape;

        if(stringRepresentation == "Space") return Key::Space;

        if(stringRepresentation == "Enter") return Key::Enter;

        if(stringRepresentation == "Backspace") return Key::Backspace;

        if(stringRepresentation == "Tab") return Key::Tab;

        if(stringRepresentation == "Left") return Key::Left;

        if(stringRepresentation == "Right") return Key::Right;

        if(stringRepresentation == "Up") return Key::Up;

        if(stringRepresentation == "Down") return Key::Down;

        if(stringRepresentation == "LShift") return Key::LShift;

        if(stringRepresentation == "RShift") return Key::RShift;
        
        if(stringRepresentation == "LControl") return Key::LControl;

        if(stringRepresentation == "RControl") return Key::RControl;

        if(stringRepresentation == "LAlt") return Key::LAlt;

        if(stringRepresentation == "RAlt") return Key::RAlt;

        return Key::A;

    }

    static constexpr Button getButton(const std::string& stringRepresentation){

        if(stringRepresentation == "Left") return Button::Left;
        
        if(stringRepresentation == "Right") return Button::Right;

        if(stringRepresentation == "Middle") return Button::Middle;

        if(stringRepresentation == "Side") return Button::Side;

        if(stringRepresentation == "Extra") return Button::Extra;

        if(stringRepresentation == "Forward") return Button::Forward;

        if(stringRepresentation == "Back") return Button::Back;

        return Button::Left;
    }

}