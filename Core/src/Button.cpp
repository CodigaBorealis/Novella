#include "../Novella/Components/UI/Button.hpp"
#include <string>
namespace Novella::UI{
    
    void Button::setSprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer){
        
        sprite.emplace(std::move(texture), style, renderLayer);
    }

    void Button::setLabel(std::shared_ptr<Font> font, int fontSize, const std::string& text, const Style& style, int renderLayer){

        if(sprite.has_value()){

            renderLayer++;
        }

        label.emplace(std::move(font), text, fontSize, style, renderLayer);
    }

    void Button::draw(Renderer& renderer){

        if(sprite.has_value()){

            sprite->draw(renderer);
        }

        if(label.has_value()){

            label->draw(renderer);
        }
    }

    void Button::updateLayout(LayoutSystem& layoutSystem, const Vector2i& parentSize){

        setComputedRectangle(layoutSystem.compute(getStyle(), parentSize));

        if(sprite.has_value()){

            sprite->setComputedRectangle(this->getComputedRectangle());
        }

        if(label.has_value()){

            label->setComputedRectangle(this->getComputedRectangle());
        }
    }
}