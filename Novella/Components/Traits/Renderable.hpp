#pragma once
#include "../../Systems/Renderer/Renderer.hpp"

namespace Novella{

    struct Color;
}

namespace Novella::Traits{

    struct Renderable{

        virtual ~Renderable() = default;

        virtual void draw(Renderer& renderer) = 0;

        int renderLayer() const {return rLayer;};

        void setRenderLayer(int layer){rLayer = layer;};

        void setColor(const Color& color){tint = color;};
                
        const Color& getColor() const{return tint;};

        private:

        int rLayer = 0;
        Color tint = {255,255,255,255};
    };  
}
