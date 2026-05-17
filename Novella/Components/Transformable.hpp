#pragma once
#include "../Math/Vector2x.hpp"

namespace Novella::Attribute{

    struct Transformable{

        virtual ~Transformable() = default;

        virtual void setPosition(const Math::Vector2i& position) = 0;

        virtual const Math::Vector2i& getPosition() const = 0;

        virtual void setDimensions(const Math::Vector2i& position) = 0;

        virtual const Math::Vector2i& getDimensions() const = 0;

    };
}
