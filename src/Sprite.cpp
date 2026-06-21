#include "../Novella/Components/UI/Sprite.hpp"
#include <raylib.h>

namespace Novella::UI{

        Sprite::Sprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer)
            :
            texture(texture),
            Traits::Layoutable(style),
            rLayer(renderLayer)
            {}

        void Sprite::draw(Renderer& renderer){

            renderer.drawTexture(*texture, computedRectangle, rotation, tint);
        }

        void Sprite::setRenderLayer(int layer){

            this->rLayer = layer;
        }
        
        int Sprite::renderLayer() const{

            return this->rLayer;
        }

        void Sprite::setColor(const Color& color){

            this->tint = color;
        }

        const Color& Sprite::getColor() const{

            return this->tint;
        }

        void Sprite::setRotation(float degrees){

            this->rotation = degrees;
        }
            
        float Sprite::getRotation() const{

            return this->rotation;
        }
}