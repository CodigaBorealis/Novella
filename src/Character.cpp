#include "../Novella/Components/Character.hpp"
#include <nlohmann/json.hpp>
#include <raylib.h>

namespace Novella::Components{

        Character::Character(std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
            :
            texture(texture),
            Attribute::Layoutable(layout)
            {}

        Character::Character(std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
            :
            texture(texture),
            Attribute::Layoutable(layout),
            rLayer(renderLayer)
            {}
            
        uint64_t Character::getID() const{

            return this->id;
        }

        void Character::setID(uint64_t id){

        this->id = id;
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

        Type Character::getType() const{

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