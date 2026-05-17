#pragma once
#include "../Graphics/Texture.hpp"
#include "../Graphics/Font.hpp"
#include "../Graphics/Image.hpp"
#include "../Graphics/Color.hpp"
#include "../Scene/Scene.hpp"
#include "../Math/Vector2x.hpp"

namespace Novella::Rendering{

    class Renderer{

        public:
        
        static void beginFrame();
        static void endFrame();

        static void drawTexture(const Graphics::Texture& texture, const Math::Vector2i& position, const Math::Vector2i& dimensions, float rotation, const Graphics::Color& tint);

        static void drawFont(const Graphics::Font& font, const std::string& text, const Math::Vector2i& position, int fontSize, float spacing, const Graphics::Color& tint);

        void drawScene(Scene& scene);

        private:

        static void sortObjects(Scene& scene);
    };
}
