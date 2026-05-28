#include "../Novella/Components/Background.hpp"
#include <nlohmann/json.hpp>

namespace Novella::Components{

       Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
            :
            texture(texture),
            id(id),
            Attribute::Layoutable(layout)
            {}

        Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
            :
            texture(texture),
            id(id),
            Attribute::Layoutable(layout),
            rLayer(renderLayer)
            {}
        
        void Background::draw(Rendering::Renderer& renderer){

            renderer.drawTexture(*texture, computedRectangle, rotation, tint);
        }

        void Background::setRenderLayer(int layer){

            this->rLayer = layer;
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

        unsigned int Background::getID() const{

            return this->id;
        }

        Type Background::getType() const{

            return this->type;
        }

        nlohmann::json Background::serialize() const{

            return {};
        }

        void Background::setRotation(float degrees){

            this->rotation = degrees;
        }
            
        float Background::getRotation() const{

            return this->rotation;
        }        

}