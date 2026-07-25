#pragma once
#include "../Traits/Object.hpp"
#include "../Traits/Clickable.hpp"
#include "../Traits/Composite.hpp"
#include "../Traits/Validatable.hpp"

namespace Novella::UI{
 
    class Button : public Traits::Composite, public Traits::Clickable, public Traits::Validatable, public Traits::RegisteredObject<Button>{

        public:
        
        Button() = default;

        void validate() const override;
    };
}