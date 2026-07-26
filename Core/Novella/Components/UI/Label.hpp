#pragma once
#include "../Primitives/Font.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Renderable.hpp"
#include "../Traits/Layoutable.hpp"
#include "../Traits/Text.hpp"
#include "../Traits/Primitive.hpp"
#include "../Traits/Transformable.hpp"

namespace Novella::UI{

    class Label: public Traits::Primitive, public Traits::Renderable, public Traits::Layoutable, public Traits::Transformable, public Traits::Text, public Traits::RegisteredObject<Label>{

        public:

        Label(std::shared_ptr<Font> font, const std::string& text);

        Label(std::shared_ptr<Font> font, const std::string& text, int size, const Style& style, int renderLayer);
        
        void draw(Renderer& renderer) override;

        const std::unordered_map<std::string, PropertyDescriptor>& properties() const override;

        Rectangle naturalSize() const override;

        void updateLayout(LayoutSystem& layoutSystem, const Rectangle& parent) override;

        Vector2x<float> measure(LayoutSystem& layout) const override;
    };
}