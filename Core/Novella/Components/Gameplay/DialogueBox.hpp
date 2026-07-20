#pragma once
#include "../Traits/Object.hpp"
#include "../Primitives/Texture.hpp"
#include "../Primitives/Font.hpp"
#include <cstddef>
#include <memory>
#include <string>
#include <vector>
#include "../UI/Sprite.hpp"
#include "../UI/Label.hpp"

namespace Novella::Gameplay{

    class DialogueBox : public Traits::RegisteredObject<DialogueBox>{

        public:
        
        struct DialogueLine{
            
            std::string backgroundID;
            std::string speaker;
            std::string text;
            std::string portraitID;
            std::string voiceClipID;
            std::string fontID;
        };

        DialogueBox();
        
        void setDialogue(size_t index);
        void setDialogueLines(std::vector<DialogueLine> lines);

        void nextLine();
        void previousLine();
        bool hasNext() const;
        void clear();
        void reset();

        const DialogueLine& currentLine() const;

        private:    

        void setBackground(std::shared_ptr<Texture> texture);
        void setPortrait(std::shared_ptr<Texture> texture);
        void setSpeaker(const std::string& name);
        void setFont(std::shared_ptr<Font> font);

        size_t currentIndex = 0;
        std::vector<DialogueLine> lines;

        UI::Sprite portrait;
        UI::Sprite background;
        UI::Label speaker;
        UI::Label text;
    };
}