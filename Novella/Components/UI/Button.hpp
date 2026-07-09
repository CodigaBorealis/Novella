#pragma once
#include "../Traits/Layoutable.hpp"
#include "../Traits/Object.hpp"
#include "../Traits/Clickable.hpp"
#include "../Traits/Renderable.hpp"
#include "../Traits/Transformable.hpp"
#include "../Traits/Texturable.hpp"

namespace Novella::UI{
 
    class Button : public Traits::Clickable, public Traits::Renderable, public Traits::Layoutable, public Traits::Transformable, public Traits::Texturable, public Traits::RegisteredObject<Button>{

        public:

        Button(std::shared_ptr<Texture> texture);

        Button(std::shared_ptr<Texture> texture, const Style& style, int renderLayer);
            
        void draw(Renderer& renderer) override;
                        
    };
}