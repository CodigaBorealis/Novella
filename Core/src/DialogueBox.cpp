#include "Novella/Components/UI/DialogueBox.hpp"
#include "Novella/Components/Gameplay/DialogueController.hpp"

#include <string>

namespace Novella::UI{

    void DialogueBox::validate() const{

    

    }

    void DialogueBox::setSpeakerText(const std::string& speaker){

        auto* controller = getChild("controller");

        if(!controller) return;
        

    }

    void DialogueBox::setDialogueText(const std::string& text){


    }

    void DialogueBox::setPortraitTexture(std::shared_ptr<Texture> texture){


    }

    void DialogueBox::setBackgroundTexture(std::shared_ptr<Texture> texture){


    }
}