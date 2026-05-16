#pragma once
#include <cstdint>
#include <raylib.h>

namespace Novella::Graphics{

    struct Color{

        constexpr Color()
            :
            red(0),
            blue(0),
            green(0),
            alpha(0)
            {}

        constexpr Color(uint8_t red, uint8_t green, uint8_t blue, uint8_t alpha)
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
        
        operator ::Color() const {

            return ::Color{
                red,
                green,
                blue,
                alpha
            };
        }
    };
    
    namespace Colors{

        inline constexpr Color Red{255, 0, 0, 255};
        inline constexpr Color Green{0, 255, 0, 255};
        inline constexpr Color Blue{0, 0, 255, 255};
        inline constexpr Color Black{0, 0, 0, 255};
        inline constexpr Color White{255, 255, 255, 255};
    
    }
}
