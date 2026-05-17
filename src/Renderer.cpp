#include "../Novella/Rendering/Renderer.hpp"
#include "../Novella/Components/Renderable.hpp"
#include <raylib.h>

namespace Novella::Rendering{

    void Renderer::drawTexture(const Graphics::Texture& texture, const Math::Vector2i& position, const Graphics::Color& tint){

        ::DrawTexture(texture.getHandle(), position.x, position.y, tint);
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

    void Renderer::drawScene(const Scene &scene){

        for(const auto& obj : scene.objects()){

            if(auto* renderable = dynamic_cast<Attribute::Renderable*>(obj.get())){

                renderable->draw(*this);
            }
        }
    }
}