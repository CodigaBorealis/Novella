#include "../Novella/Rendering/Renderer.hpp"
#include "../Novella/Attribute/Renderable.hpp"
#include "../Novella/Math/Rectangle.hpp"
#include "../Novella/Graphics/Color.hpp"
#include "../Novella/Graphics/Texture.hpp"
#include "../Novella/Graphics/Font.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Object.hpp"
#include <algorithm>
#include <raylib.h>

namespace Novella::Rendering{

    Renderer::~Renderer(){

        if(canvas.id != 0){

        ::UnloadRenderTexture(canvas);

        }

    }

    Renderer::Renderer(int width, int height){

        baseResolution = {float(width), float(height)};
        
        canvas = ::LoadRenderTexture(width, height);
    }

    void Renderer::drawTexture(const Graphics::Texture& texture, const Math::Rectangle& rect, float rotation, const Graphics::Color& tint){
        
        Math::Vector2f origin{0.f, 0.f};

        Math::Rectangle source{

            0.0f,
            0.0f,
            static_cast<float>(texture.width()),
            static_cast<float>(texture.height())
        };
        
        ::DrawTexturePro(texture.getHandle(), source, rect, origin, rotation, tint);
    }

    void Renderer::drawFont(const Graphics::Font& font, const std::string& text, const Math::Rectangle& rect, int fontSize, float spacing, const Graphics::Color& tint){

        ::DrawTextEx(font.getHandle(), text.c_str(), {rect.x, rect.y}, fontSize, spacing, tint);
    }


    void Renderer::beginFrame(){

        ::BeginTextureMode(canvas);
        ::ClearBackground(Graphics::Colors::Black);
    }
    
    void Renderer::endFrame(){
        
        ::EndTextureMode();

        ::BeginDrawing();
        ::ClearBackground(Graphics::Colors::Black);

        Math::Rectangle source{0.0f, 0.0f, baseResolution.x, -baseResolution.y};//The texture is flipped otherwise

        Math::Rectangle dest{

            renderTargetOffset.x,
            renderTargetOffset.y,
            baseResolution.x * scale,
            baseResolution.y * scale

        };

        ::DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0f, WHITE);
        ::EndDrawing();
    }

    void Renderer::sortObjects(Scene& scene){

        auto& objects = scene.objects();
        
        std::stable_sort(objects.begin(), objects.end(), [](const auto& a, const auto& b){

            auto* renderableA = dynamic_cast<Attribute::Renderable*>(a.get());
            auto* renderableB = dynamic_cast<Attribute::Renderable*>(b.get());

            int layerA = renderableA ? renderableA->renderLayer() : 0;
            int layerB = renderableB ? renderableB->renderLayer() : 0;

            return layerA < layerB;
        });

        scene.clearDirtyFlag();
    }
    
    void Renderer::drawScene(Scene &scene){

        if(scene.needsSorting()){

            sortObjects(scene);
        }

        for(const auto& obj : scene.objects()){

            if(auto* renderable = dynamic_cast<Attribute::Renderable*>(obj.get())){

                renderable->draw(*this);
            }
        }
    }

    void Renderer::resize(const Math::Vector2i& windowSize){

        if(baseResolution.x == 0 || baseResolution.y == 0) return;

        scale = std::min(
            
            static_cast<float>(windowSize.x) / baseResolution.x,
            static_cast<float>(windowSize.y) / baseResolution.y

        );

        renderTargetOffset.x = (windowSize.x - (baseResolution.x * scale)) * 0.5f;
        renderTargetOffset.y = (windowSize.y - (baseResolution.y * scale)) * 0.5f;

    }

    Math::Vector2f Renderer::virtualResolution() const{

        return baseResolution;
    }

    Math::Vector2f Renderer::toVirtualCoordinates(const Math::Vector2f& mousePosition) const{

        return{
            
            (mousePosition.x - renderTargetOffset.x) / scale,
            (mousePosition.y - renderTargetOffset.y) / scale
        };
    }    
}