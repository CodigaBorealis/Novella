#pragma once
#include "../Graphics/Font.hpp"
#include "Object.hpp"
#include "Positionable.hpp"
#include "Renderable.hpp"
#include "Clickable.hpp"
#include "Type.hpp"
#include <memory>

namespace Novella::Components{

    class Label: public Attribute::Object, public Attribute::Renderable, public Attribute::Positionable, public Attribute::Clickable{

        public:

        Label() = delete;

        Label(const std::string& id, std::shared_ptr<Graphics::Font> font, const Math::Vector2i& position, int size, const std::string& text);
        Label(const std::string& id, std::shared_ptr<Graphics::Font> font, const Math::Vector2i& position, int size, const std::string& text, int renderLayer);
        
        void draw(Rendering::Renderer& renderer) override;

        int renderLayer() const override;

        void setColor(const Graphics::Color& color) override;
        const Graphics::Color& getColor() const override;

        void setPosition(const Math::Vector2i& position) override;
        const Math::Vector2i& getPosition() const override;

        void setSize(unsigned int size);
        unsigned int getSize() const;

        void setSpacing(float spacing);

        float getSpacing() const;

        void addMouseBind(Input::Mouse button, const std::string& name, const nlohmann::json& args, const std::string& target) override;

        bool contains(const Math::Vector2f& mousePos) const override;

        const std::string& getID() const override;

        nlohmann::json serialize() const override;

        const std::string getType() const override;

        void setText(const std::string& text);
        const std::string& getText() const;
        
        void setFont(std::shared_ptr<Graphics::Font> font);

        std::shared_ptr<Graphics::Font> getFont() const;
        
        private:
        
        std::string text;
        std::shared_ptr<Graphics::Font> font;
        int size;
        float spacing = 1.0f;
        Math::Vector2i position;
        std::string id;
        int rLayer;
        Graphics::Color tint;
        static constexpr const char* TYPE = Type::Label;//This is shit but i need a way to serialize components



    };
}