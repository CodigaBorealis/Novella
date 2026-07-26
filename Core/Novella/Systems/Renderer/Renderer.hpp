#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include "../../Primitives/Color.hpp"
#include <string>
#include <vector>

namespace Novella::Traits{

    struct Renderable;
    struct Object;
}

namespace Novella{

    class Texture;
    class Font;
    class Color;
    class Scene;
    struct Rectangle;

    class Renderer{

        public:

        ~Renderer();

        Renderer() = delete;

        Renderer(int width, int height);

        void beginFrame();
        void endFrame();

        void drawTexture(const Texture* texture, const Rectangle& rect, float rotation, const Color& tint);

        void drawFont(const Font& font, const std::string& text, const Rectangle& rect, int fontSize, float spacing, const Color& tint);

        void drawScene(Scene& scene);
                
        void resize(const Vector2x<int>& windowSize);

        void drawErrorMessage(const std::string& error);
        
        void setBackgroundColor(const Color& color);

        void drawRectangle(const Rectangle& rectangle, const Color& color);
        
        Vector2x<float> virtualResolution() const;
        
        Vector2x<float> toVirtualCoordinates(const Vector2x<float>& mousePosition) const;

        private:

        void collectRenderables(Traits::Object& object, std::vector<Traits::Renderable*>& cache);

        Color backgroundColor{0,0,0,0};

        ::RenderTexture2D canvas{};
        Vector2x<float> baseResolution;
        Vector2x<float> renderTargetOffset{0.0f, 0.0f};
        float scale = 1.0f;

        std::vector<Traits::Renderable*> renderCache;

        void rebuildCache(Scene& scene);

    };
}
