#pragma once
#include "../Graphics/Texture.hpp"
#include "../Graphics/Color.hpp"
#include "../Scene/Scene.hpp"
namespace Novella::Rendering{

    class Renderer{

        public:
        
        static void beginFrame();
        static void endFrame();

        static void drawTexture(const Graphics::Texture& texture, int x, int y);
        static void drawTexture(const Graphics::Texture& texture, int x, int y, const Graphics::Color& tint);
        void drawScene(const Scene& scene);

    };
}
