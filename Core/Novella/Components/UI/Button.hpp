#pragma once
#include "../Traits/Object.hpp"
#include "../Traits/Clickable.hpp"
#include "Label.hpp"
#include "Sprite.hpp"
#include <memory>
#include <optional>

namespace Novella::UI{
 
    class Button : public Traits::Clickable, public Traits::Renderable, public Traits::Layoutable, public Traits::RegisteredObject<Button>{

        public:
        
        Button() = default;

        void updateLayout(LayoutSystem& layoutSystem, const Vector2i& parentSize) override;

        void setSprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);

        void setLabel(std::shared_ptr<Font> font, int fontSize, const std::string& text, const Style& style, int renderLayer);

        void draw(Renderer& renderer) override;

        private:
        
        std::optional<Sprite> sprite;
        std::optional<Label> label;
    };
}