#pragma once
#include "../Graphics/Texture.hpp"
#include "Object.hpp"
#include "Renderable.hpp"
#include "Type.hpp"
#include <memory>
#include "../Layout/Layout.hpp"
#include "Layoutable.hpp"

namespace Novella::Components{

    class Character : public Attribute::Object, public Attribute::Renderable, public Attribute::Layoutable{

        public:

            Character() = delete;

            Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout);
            Character(const std::string id, std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);
            
            const std::string& getID() const override;

            void draw(Rendering::Renderer& renderer) override;

            void setRenderLayer(int layer);
            int renderLayer() const override;

            nlohmann::json serialize() const override;

            const std::string getType() const override;

            void setColor(const Graphics::Color& color) override;

            const Graphics::Color& getColor() const override;

            void setRotation(float degrees);

            float getRotation() const;

        private:

            std::string id;
            std::shared_ptr<Graphics::Texture> texture;
            int rLayer = 0;
            Graphics::Color tint;
            float rotation = 0;
            //std::vector<std::string> sounds;
        static constexpr const char* type = Type::Character;//This is shit but i need a way to serialize components

    };
}