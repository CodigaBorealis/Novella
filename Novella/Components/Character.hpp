#pragma once
#include "../Graphics/Texture.hpp"
#include "../Attribute/Object.hpp"
#include "../Attribute/Renderable.hpp"
#include "Type.hpp"
#include <memory>
#include "../Layout/Layout.hpp"
#include "../Attribute/Layoutable.hpp"
#include "../Graphics/Color.hpp"

namespace Novella::Components{

    class Character : public Attribute::Object, public Attribute::Renderable, public Attribute::Layoutable{

        public:

            Character() = delete;

            Character(std::shared_ptr<Graphics::Texture> texture, const Layout& layout);
            Character(std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);
            
            uint64_t getID() const override;
            void setID(uint64_t id) override;

            void draw(Rendering::Renderer& renderer) override;

            void setRenderLayer(int layer);
            int renderLayer() const override;

            nlohmann::json serialize() const override;

            Type getType() const override;

            void setColor(const Graphics::Color& color) override;

            const Graphics::Color& getColor() const override;

            void setRotation(float degrees);

            float getRotation() const;

        private:

            uint64_t id;
            std::shared_ptr<Graphics::Texture> texture;
            int rLayer = 0;
            Graphics::Color tint;
            float rotation = 0;
            //std::vector<std::string> sounds;
            Type type = Type::Character;//This is shit but i need a way to serialize components

    };
}