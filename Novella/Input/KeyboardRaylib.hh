#pragma once
#include "Keyboard.hpp"
#include <raylib.h>

namespace Novella::Input{

    inline Keyboard fromRaylib(int key){

        switch(key){

            #define X(name, raylib) case raylib: return Keyboard::name;
            #include "Keys.hpp"
            #undef X

            default:

                return Keyboard::Unknown;
        }
    }

    inline int toRaylib(Keyboard key){

        switch(key){

            #define X(name, raylib) case Keyboard::name: return raylib;
            #include "Keys.hpp"
            #undef X

            default:

                return KEY_NULL;
        }
    }

    inline bool isPressed(Keyboard key){

        return ::IsKeyDown(toRaylib(key));
    }

}