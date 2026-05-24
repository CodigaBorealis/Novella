#pragma once
#include "../Graphics/Texture.hpp"
#include "../Graphics/Font.hpp"
#include "../Graphics/Color.hpp"
#include "../Scene/Scene.hpp"
#include "../Math/Vector2x.hpp"
#include "../Math/Rectangle.hpp"

namespace Novella::Rendering{

    class Renderer{

        public:

        ~Renderer();

        Renderer() = delete;

        Renderer(int width, int height);

        void beginFrame();
        void endFrame();

        void drawTexture(const Graphics::Texture& texture, const Math::Rectangle& rect, float rotation, const Graphics::Color& tint);

        void drawFont(const Graphics::Font& font, const std::string& text, const Math::Rectangle& rect, int fontSize, float spacing, const Graphics::Color& tint);

        void drawScene(Scene& scene);
        
        void resize(const Math::Vector2i& windowSize);

        Math::Vector2f virtualResolution() const;
        
        Math::Vector2f toVirtualCoordinates(const Math::Vector2f& mousePosition) const;

        private:

        ::RenderTexture2D canvas{};
        Math::Vector2f baseResolution;
        Math::Vector2f renderTargetOffset{0.0f, 0.0f};
        float scale = 1.0f;

        static void sortObjects(Scene& scene);

    };
}
