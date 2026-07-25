#pragma once
#include "../Traits/Object.hpp"
#include "../Traits/Composite.hpp"
#include "../Traits/Validatable.hpp"

namespace Novella{

    class ResourceManager;
}

namespace Novella::UI{

    class DialogueBox : public Traits::Composite, public Traits::Validatable, public Traits::RegisteredObject<DialogueBox>{

        public: 
        
        DialogueBox() = default;

        void validate() const override;

        void setSpeakerText(const std::string& speaker);
        void setDialogueText(const std::string& text);
        void setPortraitTexture(std::shared_ptr<Texture> texture);
        void setBackgroundTexture(std::shared_ptr<Texture> texture);
    };
}