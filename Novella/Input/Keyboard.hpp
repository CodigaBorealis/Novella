#pragma once

namespace Novella::Input{

    enum class Keyboard{

        Unknown,

        #define X(name, raylib) name,
        #include "Keys.hpp"
        #undef X

    };
}