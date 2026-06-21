#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include <string>

namespace Novella{

    class Texture;
    class Font;
    class Color;
    class Scene;
}

namespace Novella{

    struct Rectangle;

}

namespace Novella{

    class Renderer{

        public:

        ~Renderer();

        Renderer() = delete;

        Renderer(int width, int height);

        void beginFrame();
        void endFrame();

        void drawTexture(const Texture& texture, const Rectangle& rect, float rotation, const Color& tint);

        void drawFont(const Font& font, const std::string& text, const Rectangle& rect, int fontSize, float spacing, const Color& tint);

        void drawScene(Scene& scene);
                
        void resize(const Vector2i& windowSize);

        void drawErrorMessage(const std::string& error);
        
        Vector2f virtualResolution() const;
        
        Vector2f toVirtualCoordinates(const Vector2f& mousePosition) const;

        private:

        ::RenderTexture2D canvas{};
        Vector2f baseResolution;
        Vector2f renderTargetOffset{0.0f, 0.0f};
        float scale = 1.0f;

        static void sortObjects(Scene& scene);

    };
}
