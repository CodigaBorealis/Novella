#include "../Novella/Components/Background.hpp"
#include <nlohmann/json.hpp>
#include "../Novella/Components/Type.hpp"
namespace Novella::Components{

       Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout)
            :
            Attribute::Object(id, Type::Background),
            texture(texture),
            Attribute::Layoutable(layout)
            {}

        Background::Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer)
            :
            Attribute::Object(id, Type::Background),
            texture(texture),
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

        const std::string& Background::getID() const{

            return this->id;
        }

        void Background::setID(const std::string& id){

        this->id = id;
        }

        const std::string& Background::getType() const{

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