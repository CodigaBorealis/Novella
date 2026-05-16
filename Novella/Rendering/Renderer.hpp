#pragma once
#include "../Graphics/Texture.hpp"
#include "../Graphics/Color.hpp"

namespace Novella::Rendering{

    class Renderer{

        public:
                
        static void drawTexture(const Graphics::Texture& texture, int x, int y, const Graphics::Color& tint);

    };
}
