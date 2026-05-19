#pragma once
#include "Renderable.hpp"
#include <memory>
#include "Type.hpp"
#include "../Layout/Layout.hpp"
#include "Layoutable.hpp"
namespace Novella::Components {

    class Background: public Attribute::Object, public Attribute::Renderable, public Attribute::Layoutable{

        public:

        Background() = delete;

        Background(const std::string& id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout);
        Background(const std::string& id,std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);
        
        void draw(Rendering::Renderer& renderer) override;

        void setRenderLayer(int layer);
        int renderLayer() const override;
        
        void setColor(const Graphics::Color& color) override;
        const Graphics::Color& getColor() const override;

        const std::string& getID() const override;

        const std::string getType() const override;

        nlohmann::json serialize() const override;

        void setRotation(float degrees);
            
        float getRotation() const;

        private:
        
        std::shared_ptr<Graphics::Texture> texture;
        Graphics::Color tint;
        std::string id;
        int rLayer = -1;
        float rotation = 0;
        static constexpr const char* TYPE = Type::Background;//This is shit but i need a way to serialize components


    };

}