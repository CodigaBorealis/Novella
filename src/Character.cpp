#include "../Novella/Components/Character.hpp"
#include <raylib.h>

namespace Novella::Components{

        Character::Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position)
            :
            id(id),
            texture(texture),
            position(position)
            {}

        Character::Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Math::Vector2i& position, int renderLayer, const Math::Vector2i& dimensions)
            :
            id(id),
            texture(texture),
            position(position),
            rLayer(renderLayer),
            dimensions(dimensions)
            {}
            
        std::string Character::getID() const{

            return id;
        }

        void Character::draw(Rendering::Renderer& renderer){

            renderer.drawTexture(*texture, position.x, position.y, tint);
        }

        int Character::renderLayer() const{

            return rLayer;
        }

        void Character::setPosition(const Math::Vector2i& position){

            this->position = position;
        }

        const Math::Vector2i& Character::getPosition() const{

            return position;
        }

        nlohmann::json Character::serialize() const{

            return {};

        }

        void Character::setDimensions(const Math::Vector2i& dimensions){

            this->dimensions = dimensions;
        }

        const Math::Vector2i& Character::getDimensions() const{

            return dimensions;
        }

        const std::string Character::getType() const{

            return type;
        }

        void Character::setColor(const Graphics::Color& color){

            this->tint = color;
        }

        const Graphics::Color& Character::getColor() const{

            return this->tint;
        }
}