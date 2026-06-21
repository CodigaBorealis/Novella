#include "../Novella/Components/UI/Button.hpp"
#include "../Novella/Components/Primitives/Texture.hpp"
namespace Novella::UI{
    
    Button::Button(std::shared_ptr<Texture> texture, const Style& style, int renderLayer)
        :
        texture(texture),
        Traits::Layoutable(style),
        rLayer(renderLayer)
        {}
            
    bool Button::contains(const Vector2f& mousePos) const{

        return mousePos.x >= computedRectangle.x && mousePos.x <= computedRectangle.x + computedRectangle.width &&
               mousePos.y >= computedRectangle.y && mousePos.y <= computedRectangle.y + computedRectangle.height;

    }

    void Button::draw(Renderer& renderer){

        renderer.drawTexture(*texture, computedRectangle, rotation, tint);
    }

    void Button::setRenderLayer(int layer){

        this->rLayer = layer;
    }
    int Button::renderLayer() const{

        return this->rLayer;
    }

    void Button::setColor(const Color& color){

        this->tint = color;
    }

    const Color& Button::getColor() const{

        return this->tint;
    }
        
    void Button::setRotation(float degrees){

        this->rotation = degrees;
    }
            
    float Button::getRotation() const{

        return this->rotation;
    }

}