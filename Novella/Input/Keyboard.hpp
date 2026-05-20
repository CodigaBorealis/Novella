#pragma once

namespace Novella::Input::Keyboard{

    enum class Key{

        Unknown,

        #define X(name, raylib) name,
        #include "Keys.hpp"
        #undef X

    };
}