#include "../Novella/Components/Character.hpp"
#include <raylib.h>

namespace Novella::Components{

        Character::Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
            :
            id(id),
            texture(texture),
            Attribute::Layoutable(layout)
            {}

        Character::Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
            :
            id(id),
            texture(texture),
            Attribute::Layoutable(layout),
            rLayer(renderLayer)
            {}
            
        const std::string& Character::getID() const{

            return this->id;
        }

        void Character::draw(Rendering::Renderer& renderer){

            renderer.drawTexture(*texture, computedRectangle, rotation, tint);
        }

        void Character::setRenderLayer(int layer){

            this->rLayer = layer;
        }
        
        int Character::renderLayer() const{

            return this->rLayer;
        }

        nlohmann::json Character::serialize() const{

            return {};

        }

        const std::string Character::getType() const{

            return this->type;
        }

        void Character::setColor(const Graphics::Color& color){

            this->tint = color;
        }

        const Graphics::Color& Character::getColor() const{

            return this->tint;
        }

        void Character::setRotation(float degrees){

            this->rotation = degrees;
        }
            
        float Character::getRotation() const{

            return this->rotation;
        }
}