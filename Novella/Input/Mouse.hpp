#pragma once

namespace Novella::Input{

    enum class Mouse{

        Unknown,

        #define X(name, raylib) name,
        #include "MouseButtons.hpp"
        #undef X
    };
}