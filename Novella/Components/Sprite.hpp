#pragma once
#include "../Graphics/Texture.hpp"
#include "../Attribute/Object.hpp"
#include "../Attribute/Renderable.hpp"
#include <memory>
#include "../Layout/Layout.hpp"
#include "../Attribute/Layoutable.hpp"
#include "../Graphics/Color.hpp"

namespace Novella::Components{

    class Sprite : public Attribute::Object, public Attribute::Renderable, public Attribute::Layoutable{

        public:

            Sprite() = delete;

            Sprite(std::shared_ptr<Graphics::Texture> texture, const Layout& layout);
            Sprite(std::shared_ptr<Graphics::Texture> texture, const Layout& layout, int renderLayer);

            void draw(Rendering::Renderer& renderer) override;

            void setRenderLayer(int layer);
            int renderLayer() const override;

            const std::string& getType() const override;

            void setColor(const Graphics::Color& color) override;

            const Graphics::Color& getColor() const override;

            void setRotation(float degrees);

            float getRotation() const;

        private:

            std::shared_ptr<Graphics::Texture> texture;
            int rLayer = 0;
            Graphics::Color tint;
            float rotation = 0;
            //std::vector<std::string> sounds;

    };
}