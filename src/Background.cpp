#include "../Novella/Components/Background.hpp"

namespace Novella::Components{

       Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture)
            :
            texture(texture),
            id(id)
            {}

        Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, int renderLayer)
            :
            texture(texture),
            id(id),
            rLayer(renderLayer)
            {}
        
        void Background::draw(Rendering::Renderer& renderer){

            renderer.drawTexture(*texture, position.x, position.y, tint);
        }

        int Background::renderLayer() const{

            return rLayer;
        }
        
        void Background::setColor(const Graphics::Color& color){

            this->tint = color;
        }

        const Graphics::Color& Background::getColor() const{

            return this->tint;
        }

        std::string Background::getID() const{

            return this->id;
        }

        const std::string Background::getType() const{

            return this->TYPE;
        }

        nlohmann::json Background::serialize() const{

            return {};
        }

        void Background::setPosition(const Math::Vector2i& position){

            this->position = position;
        }

        const Math::Vector2i& Background::getPosition() const{

            return this->position;
        }

        void Background::setDimensions(const Math::Vector2i& dimensions){

            this->dimensions = dimensions;
        }
        const Math::Vector2i& Background::getDimensions() const{

            return dimensions;
        }
        

}