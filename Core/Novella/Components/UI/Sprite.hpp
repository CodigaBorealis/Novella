#pragma once
#include "../Primitives/Texture.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Renderable.hpp"
#include "../Traits/Texturable.hpp"
#include <memory>
#include "../../Systems/Layout/Style.hpp"
#include "../Traits/Layoutable.hpp"
#include "../Traits/Transformable.hpp"

namespace Novella::UI{

    class Sprite : public Traits::Renderable, public Traits::Layoutable, public Traits::Transformable, public Traits::Texturable, public Traits::RegisteredObject<Sprite>{

        public:

            Sprite(std::shared_ptr<Texture> texture);

            Sprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);

            void draw(Renderer& renderer) override;
    };
}