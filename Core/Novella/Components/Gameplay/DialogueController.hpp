#pragma once
#include "../Traits/Object.hpp"
#include <cstddef>
#include <vector>
#include <string>

namespace Novella{

    class ResourceManager;
}

namespace Novella::UI{

    class DialogueBox;
}

namespace Novella::Gameplay{

    struct DialogueLine{

        std::string backgroundID;
        std::string speaker;
        std::string speakerFontID;
        std::string text;
        std::string textFontID;
        std::string portraitID;
        std::string voiceClipID;
    };

    class DialogueController : public Traits::RegisteredObject<DialogueController>{

        public:

            DialogueController() = default;

            void bindView(UI::DialogueBox* box);

            void setLines(std::vector<DialogueLine> lines);

            void nextLine(const ResourceManager& resources);

            void previousLine(const ResourceManager& resources);

            bool hasNext() const;
            void reset();

        private:

        void syncView(const ResourceManager& resources);

        size_t currentIndex = 0;
        std::vector<DialogueLine> lines;
        UI::DialogueBox* targetView = nullptr;
    };

}