#include "../Novella/Components/UI/Sprite.hpp"
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
        }
}