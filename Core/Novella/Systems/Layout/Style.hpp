#pragma once
#include "../../Core/Math/Vector2x.hpp"

namespace Novella{

    enum class Anchor : short{

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

        enum class SizeMode : short{

        Fixed,
        Percent,
        FitWidth,
        FitHeight,
        FitContent
        };
        
    struct Style{

        Anchor anchor = Anchor::Center;

        SizeMode widthMode = SizeMode::FitContent;
        SizeMode heightMode  = SizeMode::FitContent;
        
        int32_t width = 100;
        int32_t height = 100;

        float widthPercent = 100.0f;
        float heightPercent = 100.0f;

        Vector2x<int> offset{0, 0};

    };

}