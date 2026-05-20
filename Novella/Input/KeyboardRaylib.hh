#pragma once
#include "Keyboard.hpp"
#include <raylib.h>

namespace Novella::Input::Keyboard{

    inline Key fromRaylib(int key){

        switch(key){

            #define X(name, raylib) case raylib: return Key::name;
            #include "Keys.hpp"
            #undef X

            default:

                return Key::Unknown;
        }
    }

    inline int toRaylib(Key key){

        switch(key){

            #define X(name, raylib) case Key::name: return raylib;
            #include "Keys.hpp"
            #undef X

            default:

                return KEY_NULL;
        }
    }

    inline bool isPressed(Key key){

        return ::IsKeyDown(toRaylib(key));
    }

}