#pragma once
#include "../Primitives/Font.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Renderable.hpp"
#include "../Traits/Clickable.hpp"
#include "../Traits/Layoutable.hpp"
#include "../Traits/Text.hpp"

namespace Novella::UI{

    class Label: public Traits::Renderable, public Traits::Clickable, public Traits::Layoutable, public Traits::Text, public Traits::RegisteredObject<Label>{

        public:

        Label(std::shared_ptr<Font> font, const std::string& text);

        Label(std::shared_ptr<Font> font, int size, const std::string& text, const Style& style, int renderLayer);
        
        void computeSize(const Vector2i& parentSize) override;

        void draw(Renderer& renderer) override;
    };
}