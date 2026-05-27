#pragma once
#include "Layoutable.hpp"
#include "Object.hpp"
#include "Clickable.hpp"
#include "Renderable.hpp"
#include "Type.hpp"
#include "../Layout/Layout.hpp"

namespace Novella::Components{
 
    class Button : public Attribute::Object, public Attribute::Clickable, public Attribute::Renderable, public Attribute::Layoutable{

        public:

        Button() = delete;

        Button(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout);

        Button(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);

        const std::string& getID() const override;

        nlohmann::json serialize() const override;

        const std::string getType() const override;

        void addMouseBind(Input::Mouse::Button button, const Input::ActionCommand& command) override;
            
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

        std::string id;
        std::shared_ptr<Graphics::Texture> texture;
        int rLayer = 0;
        //Label* label;
        Graphics::Color tint;
        float rotation = 0;
        static constexpr const char* type = Type::Button;//This is shit but i need a way to serialize components

    };
}