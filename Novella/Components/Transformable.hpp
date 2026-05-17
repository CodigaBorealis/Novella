#pragma once
#include "../Math/Vector2x.hpp"

namespace Novella::Attribute{

    struct Transformable{

        virtual ~Transformable() = default;

        virtual void setDimensions(const Math::Vector2i& dimensions) = 0;

        virtual const Math::Vector2i& getDimensions() const = 0;

    };
}
