#pragma once
#include "../Attribute/Renderable.hpp"
#include <memory>
#include "Type.hpp"
#include "../Layout/Layout.hpp"
#include "../Attribute/Layoutable.hpp"
#include "../Attribute/Object.hpp"
#include "../Graphics/Color.hpp"

namespace Novella::Components {

    class Background: public Attribute::Object, public Attribute::Renderable, public Attribute::Layoutable{

        public:

        Background() = delete;

        Background(std::shared_ptr<Graphics::Texture> texture, const Layout& layout);
        Background(std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);
        
        void draw(Rendering::Renderer& renderer) override;

        void setRenderLayer(int layer);
        int renderLayer() const override;
        
        void setColor(const Graphics::Color& color) override;
        const Graphics::Color& getColor() const override;

        uint64_t getID() const override;
        void setID(uint64_t id) override;

        Type getType() const override;

        nlohmann::json serialize() const override;

        void setRotation(float degrees);
            
        float getRotation() const;

        private:
        
        std::shared_ptr<Graphics::Texture> texture;
        Graphics::Color tint;
        uint64_t id;
        int rLayer = -1;
        float rotation = 0;
        Type type = Type::Background;//This is shit but i need a way to serialize components


    };

}