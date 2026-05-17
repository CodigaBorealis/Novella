#pragma once
#include "../Math/Vector2x.hpp"
namespace Novella::Attribute{

    struct Positionable{

        virtual ~Positionable() = default;

        virtual void setPosition(const Math::Vector2i& position) = 0;

        virtual const Math::Vector2i& getPosition() const = 0;
    };
}
