#include "../Novella/Rendering/Renderer.hpp"
#include "../Novella/Components/Renderable.hpp"
#include <raylib.h>

namespace Novella::Rendering{

    void Renderer::drawTexture(const Graphics::Texture& texture, int x, int y){

        ::DrawTexture(texture.getHandle(), x, y, Graphics::Colors::White);
    }
    void Renderer::drawTexture(const Graphics::Texture& texture, int x, int y, const Graphics::Color& tint){

        ::DrawTexture(texture.getHandle(), x, y, tint);
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