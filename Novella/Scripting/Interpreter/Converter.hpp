#pragma once
#include <string>
#include <variant>

namespace Novella{

    struct MouseEvent;
    struct KeyboardEvent;
}

namespace Novella::NScript::Runtime{

    class Converter{

        using InputEvent = std::variant<MouseEvent, KeyboardEvent>;

        public:

        static std::string getInputFromEvent(const MouseEvent& event);

        static std::string getInputFromEvent(const KeyboardEvent& event);

        static std::string getInputFromEvent(const InputEvent& event);

        private:

        static std::string mouseButtonToString(const MouseEvent& event);
        static std::string keyboardKeyToString(const KeyboardEvent& event);


    };

}