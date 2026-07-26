#pragma once
#include "../Primitives/Texture.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Widget.hpp"
#include "../Traits/Texturable.hpp"
#include <memory>
#include "../../Systems/Layout/Style.hpp"
#include "../Traits/Transformable.hpp"
#include "../Traits/Primitive.hpp"

namespace Novella::UI{

    class Sprite : public Traits::Primitive, public Traits::Widget, public Traits::Transformable, public Traits::Texturable, public Traits::RegisteredObject<Sprite>{

        public:

            Sprite(std::shared_ptr<Texture> texture);

            Sprite(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);

            void draw(Renderer& renderer) override;
            
            const std::unordered_map<std::string, PropertyDescriptor>& properties() const override;

            void updateLayout(LayoutSystem& layout, const Rectangle& parent) override;
            
            Vector2x<float> measure(LayoutSystem& layout) const override;
            Rectangle naturalSize() const override;
    };
}