#pragma once
#include "../Rendering/Renderer.hpp"

namespace Novella::Attribute{

    struct Renderable{

        virtual ~Renderable() = default;

        virtual void draw(Rendering::Renderer& renderer) = 0;

        virtual int renderLayer() const = 0;

        virtual void setColor(const Graphics::Color& color) = 0;
        virtual const Graphics::Color& getColor() const = 0;
    };  
}
