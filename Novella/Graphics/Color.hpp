#pragma once
#include <cstdint>

namespace Novella::Graphics{

    struct Color{

        Color() = delete;

        Color(uint8_t red, uint8_t blue, uint8_t green, uint8_t alpha)
            :
            red(red),
            green(green),
            blue(blue),
            alpha(alpha)
            {}

        uint8_t red;
        uint8_t green;
        uint8_t blue;
        uint8_t alpha;

    };
    
}