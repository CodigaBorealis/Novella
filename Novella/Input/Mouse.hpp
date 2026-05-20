#pragma once

namespace Novella::Input::Mouse{

    enum class Button{

        Unknown,

        #define X(name, raylib) name,
        #include "MouseButtons.hpp"
        #undef X
    };
}