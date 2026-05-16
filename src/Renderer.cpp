#include "../Novella/Rendering/Renderer.hpp"
#include <raylib.h>

namespace Novella::Rendering{

    void Renderer::drawTexture(const Graphics::Texture& texture, int x, int y, const Graphics::Color& tint){

        ::DrawTexture(texture.getHandle(), x, y, tint);
    }

}