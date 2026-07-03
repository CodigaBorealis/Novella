#include "../Novella/Systems/Renderer/Renderer.hpp"
#include "../Novella/Components/Traits/Renderable.hpp"
#include "../Novella/Core/Math/Rectangle.hpp"
#include "../Novella/Components/Primitives/Color.hpp"
#include "../Novella/Components/Primitives/Texture.hpp"
#include "../Novella/Components/Primitives/Font.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Object.hpp"
#include <algorithm>
#include <raylib.h>

namespace Novella{

    Renderer::~Renderer(){

        if(canvas.id != 0){

        ::UnloadRenderTexture(canvas);

        }

    }

    Renderer::Renderer(int width, int height){

        baseResolution = {float(width), float(height)};
        
        canvas = ::LoadRenderTexture(width, height);
    }

    void Renderer::drawTexture(const Texture& texture, const Rectangle& rect, float rotation, const Color& tint){
        
        Vector2f origin{0.f, 0.f};

        Rectangle source{

            0.0f,
            0.0f,
            static_cast<float>(texture.width()),
            static_cast<float>(texture.height())
        };
        
        ::DrawTexturePro(texture.getHandle(), source, rect, origin, rotation, tint);
    }

    void Renderer::drawFont(const Font& font, const std::string& text, const Rectangle& rect, int fontSize, float spacing, const Color& tint){

        ::DrawTextEx(font.getHandle(), text.c_str(), {rect.x, rect.y}, fontSize, spacing, tint);
    }


    void Renderer::beginFrame(){

        ::BeginTextureMode(canvas);
        ::ClearBackground(Colors::Black);
    }
    
    void Renderer::endFrame(){
        
        ::EndTextureMode();

        ::BeginDrawing();
        ::ClearBackground(Colors::Black);

        Rectangle source{0.0f, 0.0f, baseResolution.x, -baseResolution.y};//The texture is flipped otherwise

        Rectangle dest{

            renderTargetOffset.x,
            renderTargetOffset.y,
            baseResolution.x * scale,
            baseResolution.y * scale

        };

        ::DrawTexturePro(canvas.texture, source, dest, {0, 0}, 0.0f, WHITE);
        ::EndDrawing();
    }

    void Renderer::rebuildCache(Scene& scene){
        
        scene.forEachObject([this](Traits::Object& object){

            if(auto* renderable = dynamic_cast<Traits::Renderable*>(&object)){

                renderCache.push_back(renderable);
            }
        });

        std::stable_sort(renderCache.begin(), renderCache.end(), [](const auto* a, const auto* b){

            return a->renderLayer() < b->renderLayer();
        });

        scene.clearDirtyFlag();
    }
    
    void Renderer::drawScene(Scene &scene){

        if(scene.needsSorting()){

            renderCache.clear();
            
            rebuildCache(scene);
        }

        for(const auto& renderable : renderCache){

            renderable->draw(*this);
        }
    }

    void Renderer::resize(const Vector2i& windowSize){

        if(baseResolution.x == 0 || baseResolution.y == 0) return;

        scale = std::min(
            
            static_cast<float>(windowSize.x) / baseResolution.x,
            static_cast<float>(windowSize.y) / baseResolution.y

        );

        renderTargetOffset.x = (windowSize.x - (baseResolution.x * scale)) * 0.5f;
        renderTargetOffset.y = (windowSize.y - (baseResolution.y * scale)) * 0.5f;

    }

    Vector2f Renderer::virtualResolution() const{

        return baseResolution;
    }

    Vector2f Renderer::toVirtualCoordinates(const Vector2f& mousePosition) const{

        return{
            
            (mousePosition.x - renderTargetOffset.x) / scale,
            (mousePosition.y - renderTargetOffset.y) / scale
        };
    }    

    void Renderer::drawErrorMessage(const std::string& error){

        ::DrawText(error.c_str(), 10, 10, 40, Colors::Red);
    }

}