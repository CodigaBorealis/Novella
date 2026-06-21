#pragma once
#include "../../Core/Math/Vector2x.hpp"

namespace Novella::Traits{

    struct Clickable{

        virtual ~Clickable() = default;
                        
        virtual bool contains(const Vector2f& mousePos) const = 0;
        
    };
}
