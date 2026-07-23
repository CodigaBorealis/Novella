#pragma once
#include "../Traits/Object.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include "../UI/Sprite.hpp"
#include "../UI/Label.hpp"
#include <optional>

namespace Novella{

    class ResourceManager;
}

namespace Novella::Gameplay{

    class DialogueBox : public Traits::Renderable, public Traits::Layoutable, public Traits::RegisteredObject<DialogueBox>{

        public: 
        
        DialogueBox() = default;

        struct DialogueLine{
            
            std::string backgroundID;
            std::string speaker;
            std::string speakerFontID;
            std::string text;
            std::string textFontID;
            std::string portraitID;
            std::string voiceClipID;
        };
        
        void setDialogue(size_t index);
        void setDialogueLines(std::vector<DialogueLine> lines);

        void nextLine();
        void previousLine();
        bool hasNext() const;
        void clear();
        void reset();

        void draw(Renderer& renderer) override;
        void updateLayout(LayoutSystem& layoutSystem, const Vector2i& parentSize) override;

        const DialogueLine& currentLine() const;

        private:    

        void applyCurrentDialogue(const ResourceManager& resourceManger);

        size_t currentIndex = 0;
        std::vector<DialogueLine> lines;

        std::optional<UI::Sprite> portrait;
        std::optional<UI::Sprite> background;
        std::optional<UI::Label> speaker;
        std::optional<UI::Label> text;
        std::optional<std::string> voiceClip;
    };
}