#pragma once
#include "../Traits/Layoutable.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Clickable.hpp"
#include "../Traits/Renderable.hpp"
#include "../Primitives/Color.hpp"
#include "../Primitives/Texture.hpp"
#include <memory>

namespace Novella::UI{
 
    class Button : public Traits::Clickable, public Traits::Renderable, public Traits::Layoutable, public Traits::RegisteredObject<Button>{

        public:

        Button() = delete;

        Button(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);
            
        bool contains(const Vector2f& mousePos) const override;

        void draw(Renderer& renderer) override;
        
        void setRenderLayer(int layer);
        int renderLayer() const override;

        void setColor(const Color& color) override;
        
        const Color& getColor() const override;
        
        void setRotation(float degrees);
            
        float getRotation() const;

        private:

        std::shared_ptr<Texture> texture;
        int rLayer = 0;
        Color tint;
        float rotation = 0;

    };
}