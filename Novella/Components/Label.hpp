#pragma once
#include "../Graphics/Font.hpp"
#include "../Graphics/Color.hpp"
#include "../Attribute/Object.hpp"
#include "../Attribute/Renderable.hpp"
#include "../Attribute/Clickable.hpp"
#include "Type.hpp"
#include <memory>
#include "../Layout/Layout.hpp"
#include "../Attribute/Layoutable.hpp"

namespace Novella::Components{

    class Label: public Attribute::Object, public Attribute::Renderable, public Attribute::Clickable, public Attribute::Layoutable{

        public:

        Label() = delete;

        Label(std::shared_ptr<Graphics::Font> font, int size, const std::string& text, const Layout& layout);
        Label(std::shared_ptr<Graphics::Font> font, int size, const std::string& text, const Layout& layout, int renderLayer);
        
        void draw(Rendering::Renderer& renderer) override;

        int renderLayer() const override;

        void setColor(const Graphics::Color& color) override;
        const Graphics::Color& getColor() const override;

        void setSize(unsigned int size);
        unsigned int getSize() const;

        void setSpacing(float spacing);

        float getSpacing() const;

        bool contains(const Math::Vector2f& mousePos) const override;

        uint64_t getID() const override;
        void setID(uint64_t id) override;

        nlohmann::json serialize() const override;

        Type getType() const override;

        void setText(const std::string& text);
        const std::string& getText() const;
        
        void setFont(std::shared_ptr<Graphics::Font> font);

        std::shared_ptr<Graphics::Font> getFont() const;
        
        void computeSize(const Math::Vector2i& parentSize);

        private:
        
        std::string text;
        std::shared_ptr<Graphics::Font> font;
        int size;
        float spacing = 1.0f;
        uint64_t id;
        int rLayer;
        Graphics::Color tint;
        Type type = Type::Label;//This is shit but i need a way to serialize components



    };
}