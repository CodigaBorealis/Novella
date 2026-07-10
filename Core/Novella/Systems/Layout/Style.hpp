#pragma once
#include "../../Core/Math/Vector2x.hpp"

namespace Novella{

    enum class Anchor : int{

        TopLeft,
        TopCenter,
        TopRight,

        CenterLeft,
        Center,
        CenterRight,

        BottomLeft,
        BottomCenter,
        BottomRight
        };

        enum class SizeMode : int{

        Fixed,
        Percent,
        FitWidth,
        FitHeight
        };
        
    struct Style{

        Anchor anchor = Anchor::Center;

        SizeMode widthMode = SizeMode::Fixed;
        SizeMode heightMode  = SizeMode::Fixed;
        
        int width = 100.0f;
        int height = 100.0f;

        float widthPercent = 100.0f;
        float heightPercent = 100.0f;

        Vector2i offset{0, 0};

    };

}