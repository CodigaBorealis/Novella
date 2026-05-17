#pragma once
#include "Positionable.hpp"
#include "Renderable.hpp"
#include "Transformable.hpp"
#include <memory>
#include "Type.hpp"
namespace Novella::Components {

    class Background: public Attribute::Object, public Attribute::Renderable, public Attribute::Transformable, public Attribute::Positionable{

        public:

        Background() = delete;

        Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture);
        Background(const std::string& id,std::shared_ptr<Graphics::Texture> texture, int renderLayer);
        
        void draw(Rendering::Renderer& renderer) override;

        void setRenderLayer(int layer);
        
        int renderLayer() const override;
        
        void setColor(const Graphics::Color& color) override;
        const Graphics::Color& getColor() const override;

        const std::string& getID() const override;

        const std::string getType() const override;

        nlohmann::json serialize() const override;

        void setPosition(const Math::Vector2i& position) override;
        const Math::Vector2i& getPosition() const override;

        void setDimensions(const Math::Vector2i& position) override;
        const Math::Vector2i& getDimensions() const override;

        void setRotation(float degrees);
            
        float getRotation() const;

        private:
        
        std::shared_ptr<Graphics::Texture> texture;
        Math::Vector2i position{};
        Math::Vector2i dimensions{texture->width(), texture->height()};
        Graphics::Color tint;
        std::string id;
        int rLayer = -1;
        float rotation = 0;
        static constexpr const char* TYPE = Type::Background;//This is shit but i need a way to serialize components


    };

}