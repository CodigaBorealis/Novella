#include "Novella/Components/UI/Sprite.hpp"
#include <raylib.h>
namespace Novella::UI{

        Sprite::Sprite(std::shared_ptr<Texture> texture){

            setTexture(texture);
        }

        Sprite::Sprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer){

            setTexture(texture);
            setRenderLayer(renderLayer);
            setStyle(style);
        }

        void Sprite::draw(Renderer& renderer){
            
            renderer.drawTexture(getTexture().get(), getComputedRectangle(), getRotation(), getColor());

            renderer.drawRectangle(getComputedRectangle(),Colors::Red);
        }
        
        Rectangle Sprite::naturalSize() const{

            return {0, 0, static_cast<float>(getTexture()->width()), static_cast<float>(getTexture()->height())};
        }

        void Sprite::updateLayout(LayoutSystem& layout, const Rectangle& parent){

            setComputedRectangle(layout.compute(getStyle(), parent, naturalSize()));
        }

        const std::unordered_map<std::string, Sprite::PropertyDescriptor>& Sprite::properties() const{

            return {};
        }
        
        Vector2x<float> Sprite::measure(LayoutSystem& layout) const{

            if(style.widthMode == SizeMode::Fixed && style.heightMode == SizeMode::Fixed){

                return{static_cast<float>(style.width), static_cast<float>(style.height)};
            }

            return{static_cast<float>(getTexture()->width()), static_cast<float>(getTexture()->height())};
        }
}