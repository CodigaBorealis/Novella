#include "../Novella/Components/UI/Button.hpp"
#include "../Novella/Components/Primitives/Texture.hpp"
namespace Novella::UI{
    
    Button::Button(std::shared_ptr<Texture> texture){

        setTexture(texture);
    }

    Button::Button(std::shared_ptr<Texture> texture, const Style& style, int renderLayer){

        setTexture(texture);
        setStyle(style);
        setRenderLayer(renderLayer);
    }

    void Button::draw(Renderer& renderer){

        renderer.drawTexture(*getTexture(), getComputedRectangle(), getRotation(), getColor());
    }
}