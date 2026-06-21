#pragma once
#include "Anchor.hpp"
#include "SizeMode.hpp"
#include "../../Core/Math/Vector2x.hpp"

namespace Novella{

    struct Style{

        Anchor anchor = Anchor::TopLeft;

        SizeMode widthMode = SizeMode::Fixed;
        SizeMode heightMode  = SizeMode::Fixed;
        
        int width = 0.0f;
        int height = 0.0f;

        float widthPercent = 100.0f;
        float heightPercent = 100.0f;

        Vector2i offset{0, 0};

    };

}