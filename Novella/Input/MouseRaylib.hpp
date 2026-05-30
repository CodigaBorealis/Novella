#pragma once
#include "Mouse.hpp"
#include <raylib.h>

namespace Novella::Input::Mouse{

    inline Button fromRaylib(int button){

        switch(button){
            
            #define X(name, raylib) case raylib: return Button::name;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return Button::Left;
        }
    }

    inline int toRaylib(Button button){

        switch (button) {
            
            #define X(name, raylib) case Button::name: return raylib;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return MOUSE_BUTTON_LEFT;
        }
    }

    inline bool isPressed(Button button){return ::IsMouseButtonDown(toRaylib(button));}
}