#include "../Novella/Components/Sprite.hpp"
#include <nlohmann/json.hpp>
#include <raylib.h>
#include "../Novella/Components/Type.hpp"

namespace Novella::Components{

        Sprite::Sprite(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
            :
            Attribute::Object(id, Type::Sprite),
            texture(texture),
            Attribute::Layoutable(layout)
            {}

        Sprite::Sprite(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
            :
            Attribute::Object(id, Type::Sprite),
            texture(texture),
            Attribute::Layoutable(layout),
            rLayer(renderLayer)
            {}
            
        const std::string& Sprite::getID() const{

            return this->id;
        }

        void Sprite::setID(const std::string& id){

        this->id = id;
        }

        void Sprite::draw(Rendering::Renderer& renderer){

            renderer.drawTexture(*texture, computedRectangle, rotation, tint);
        }

        void Sprite::setRenderLayer(int layer){

            this->rLayer = layer;
        }
        
        int Sprite::renderLayer() const{

            return this->rLayer;
        }

        const std::string& Sprite::getType() const{

            return this->type;
        }

        void Sprite::setColor(const Graphics::Color& color){

            this->tint = color;
        }

        const Graphics::Color& Sprite::getColor() const{

            return this->tint;
        }

        void Sprite::setRotation(float degrees){

            this->rotation = degrees;
        }
            
        float Sprite::getRotation() const{

            return this->rotation;
        }
}