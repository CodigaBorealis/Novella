#pragma once
#include <string>
#include <variant>

namespace Novella::Input{

    struct KeyEvent;

    struct ClickEvent;
}

namespace Novella::Syntax::NovellaScript{

    class Converter{

        using InputEvent = std::variant<Input::KeyEvent, Input::ClickEvent>;

        public:

        static std::string getInputFromEvent(const Input::ClickEvent& event);

        static std::string getInputFromEvent(const Input::KeyEvent& event);

        static std::string getInputFromEvent(const InputEvent& event);

        private:

        static std::string mouseButtonToString(const Input::ClickEvent& event);
        static std::string keyboardKeyToString(const Input::KeyEvent& event);


    };

}