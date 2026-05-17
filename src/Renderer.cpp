#include "../Novella/Rendering/Renderer.hpp"
#include "../Novella/Components/Renderable.hpp"
#include "../Novella/Math/Rectangle.hpp"
#include <algorithm>
#include <raylib.h>

namespace Novella::Rendering{

    void Renderer::drawTexture(const Graphics::Texture& texture, const Math::Vector2i& position, const Math::Vector2i& dimensions, float rotation, const Graphics::Color& tint){

        Math::Vector2f origin{dimensions / 2.0f};

        Math::Rectangle source{
            0,
            0,
            static_cast<float>(texture.width()),
            static_cast<float>(texture.height())
        };

        Math::Rectangle dest{

            static_cast<float>(position.x),
            static_cast<float>(position.y),
            static_cast<float>(dimensions.x),
            static_cast<float>(dimensions.y),
        };

        ::DrawTexturePro(texture.getHandle(), source, dest, origin, rotation, tint);
    }

    void Renderer::drawFont(const Graphics::Font& font, const std::string& text, const Math::Vector2i& position, int fontSize, float spacing, const Graphics::Color& tint){

        ::DrawTextEx(font.getHandle(), text.c_str(), position, fontSize, spacing ,tint);
    }


    void Renderer::beginFrame(){

        ::BeginDrawing();
    }
    
    void Renderer::endFrame(){

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
}