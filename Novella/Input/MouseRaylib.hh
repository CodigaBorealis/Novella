#pragma once
#include "Mouse.hpp"
#include <raylib.h>

namespace Novella::Input{

    inline Mouse fromRaylib(int button){

        switch(button){
            
            #define X(name, raylib) case raylib: return Mouse::name;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return Mouse::Unknown;
        }
    }

    inline int toRaylib(Mouse button){

        switch (button) {
            
            #define X(name, raylib) case Mouse::name: return raylib;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return MOUSE_BUTTON_LEFT;
        }
    }

    inline bool isPressed(Mouse button){return ::IsMouseButtonDown(toRaylib(button));}
}