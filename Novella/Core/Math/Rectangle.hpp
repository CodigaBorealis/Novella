#pragma once
#include <raylib.h>

namespace Novella{

    struct Rectangle{

        constexpr Rectangle() = default;

        constexpr Rectangle(float x, float y, float width, float height)
            :
            x(x),
            y(y),
            width(width),
            height(height)
            {}

       constexpr Rectangle(const ::Rectangle& raylibRectangle)
            :
            x(raylibRectangle.x),
            y(raylibRectangle.y),
            width(raylibRectangle.width),
            height(raylibRectangle.height)
            {}

        constexpr operator ::Rectangle() const{

            return{

                x,
                y,
                width,
                height
            };
        } 
        
        float x = 0.f;
        float y = 0.f;
        float width = 0.f;
        float height = 0.f;
    };

}