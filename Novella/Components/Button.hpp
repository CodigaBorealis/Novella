#pragma once
#include "../Attribute/Layoutable.hpp"
#include "../Attribute/Object.hpp"
#include "../Attribute/Clickable.hpp"
#include "../Attribute/Renderable.hpp"
#include "../Layout/Layout.hpp"
#include "../Graphics/Color.hpp"

namespace Novella::Components{
 
    class Button : public Attribute::Object, public Attribute::Clickable, public Attribute::Renderable, public Attribute::Layoutable{

        public:

        Button() = delete;

        Button(std::shared_ptr<Graphics::Texture> texture, const Layout& layout);

        Button(std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);

        const std::string& getType() const override;
            
        bool contains(const Math::Vector2f& mousePos) const override;

        //void setLabel(Label* label);

        //Label* getLabel() const;

        //Label* getLabel();

        void draw(Rendering::Renderer& renderer) override;
        
        void setRenderLayer(int layer);
        int renderLayer() const override;

        void setColor(const Graphics::Color& color) override;
        
        const Graphics::Color& getColor() const override;
        
        void setRotation(float degrees);
            
        float getRotation() const;

        private:

        std::shared_ptr<Graphics::Texture> texture;
        int rLayer = 0;
        //Label* label;
        Graphics::Color tint;
        float rotation = 0;

    };
}