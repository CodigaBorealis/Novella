#pragma once
#include "../Traits/Object.hpp"
#include "../Traits/Interactable.hpp"
#include "../Traits/Composite.hpp"
#include "../Traits/Validatable.hpp"

namespace Novella::UI{
 
    class Button : public Traits::Composite, public Traits::Interactable, public Traits::Validatable, public Traits::RegisteredObject<Button>{

        public:
        
        Button() = default;

        void validate() const override;

        void handleEvent(const Event& event) override;
    };
}