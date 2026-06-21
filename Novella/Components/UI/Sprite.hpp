#pragma once
#include "../Primitives/Texture.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Renderable.hpp"
#include <memory>
#include "../../Systems/Layout/Style.hpp"
#include "../Traits/Layoutable.hpp"
#include "../Primitives/Color.hpp"

namespace Novella::UI{

    class Sprite : public Traits::Renderable, public Traits::Layoutable, public Traits::RegisteredObject<Sprite>{

        public:

            Sprite() = delete;

            Sprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);

            void draw(Renderer& renderer) override;

            void setRenderLayer(int layer);
            int renderLayer() const override;

            void setColor(const Color& color) override;

            const Color& getColor() const override;

            void setRotation(float degrees);

            float getRotation() const;

        private:

            std::shared_ptr<Texture> texture;
            int rLayer = 0;
            Color tint;
            float rotation = 0;
    };
}