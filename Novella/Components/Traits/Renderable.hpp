#pragma once
#include "../../Systems/Renderer/Renderer.hpp"

namespace Novella{

    struct Color;
}

namespace Novella::Traits{

    struct Renderable{

        virtual ~Renderable() = default;

        virtual void draw(Renderer& renderer) = 0;

        virtual int renderLayer() const = 0;

        virtual void setColor(const Color& color) = 0;
        
        virtual const Color& getColor() const = 0;

    };  
}
