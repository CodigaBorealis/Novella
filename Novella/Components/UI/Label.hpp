#pragma once
#include "../Primitives/Font.hpp"
#include "../Primitives/Color.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Renderable.hpp"
#include "../Traits/Clickable.hpp"
#include <memory>
#include "../Traits/Layoutable.hpp"

namespace Novella::UI{

    class Label: public Traits::Renderable, public Traits::Clickable, public Traits::Layoutable, public Traits::RegisteredObject<Label>{

        public:

        Label() = delete;

        Label(std::shared_ptr<Font> font, int size, const std::string& text, const Style& style, int renderLayer);
        
        void draw(Renderer& renderer) override;

        int renderLayer() const override;

        void setColor(const Color& color) override;
        const Color& getColor() const override;

        void setSize(unsigned int size);
        unsigned int getSize() const;

        void setSpacing(float spacing);

        float getSpacing() const;

        bool contains(const Vector2f& mousePos) const override;

        void setText(const std::string& text);
        const std::string& getText() const;
        
        void setFont(std::shared_ptr<Font> font);

        std::shared_ptr<Font> getFont() const;
        
        void computeSize(const Vector2i& parentSize);

        private:
        
        std::string text;
        std::shared_ptr<Font> font;
        int size;
        float spacing = 1.0f;
        int rLayer;
        Color tint;

    };
}