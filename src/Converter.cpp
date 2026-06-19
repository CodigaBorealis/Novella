#include "../Novella/Syntax/NovellaScript/Interpreter/Converter.hpp"
#include "../Novella/Input/KeyEvent.hpp"
#include "../Novella/Input/ClickEvent.hpp"
#include <stdexcept>
#include <variant>

namespace Novella::Syntax::NovellaScript{


    std::string Converter::getInputFromEvent(const Input::ClickEvent& event){

        return mouseButtonToString(event);
    }


    std::string Converter::getInputFromEvent(const Input::KeyEvent& event){

        return keyboardKeyToString(event);
    }

    std::string Converter::getInputFromEvent(const InputEvent& event){

        if(std::holds_alternative<Input::ClickEvent>(event)){

            auto& button = std::get<Input::ClickEvent>(event);

            return mouseButtonToString(button);

        }else if(std::holds_alternative<Input::KeyEvent>(event)){

            auto& key = std::get<Input::KeyEvent>(event);

            return keyboardKeyToString(key);
        }

        throw std::runtime_error("Invalid input type");
    }

    std::string Converter::mouseButtonToString(const Input::ClickEvent& event){

        switch(event.button){

            case Input::Mouse::Button::Back: return "BACK";
            case Input::Mouse::Button::Extra: return "EXTRA";
            case Input::Mouse::Button::Forward: return "FORWARD";
            case Input::Mouse::Button::Side: return "SIDE";
            case Input::Mouse::Button::Left: return "LEFT";
            case Input::Mouse::Button::Right: return "RIGHT";
            case Input::Mouse::Button::Middle: return "MIDDLE";

            default: return "UNKNOWN";
        }   
    }

    std::string Converter::keyboardKeyToString(const Input::KeyEvent& event){


        switch(event.key){

            case Input::Keyboard::Key::A: return "A";
            case Input::Keyboard::Key::B: return "B";
            case Input::Keyboard::Key::C: return "C";
            case Input::Keyboard::Key::D: return "D";
            case Input::Keyboard::Key::E: return "E";
            case Input::Keyboard::Key::F: return "F";
            case Input::Keyboard::Key::G: return "G";
            case Input::Keyboard::Key::H: return "H";
            case Input::Keyboard::Key::I: return "I";
            case Input::Keyboard::Key::J: return "J";
            case Input::Keyboard::Key::K: return "K";
            case Input::Keyboard::Key::L: return "L";
            case Input::Keyboard::Key::M: return "M";
            case Input::Keyboard::Key::N: return "N";
            case Input::Keyboard::Key::O: return "O";
            case Input::Keyboard::Key::P: return "P";
            case Input::Keyboard::Key::Q: return "Q";
            case Input::Keyboard::Key::R: return "R";
            case Input::Keyboard::Key::S: return "S";
            case Input::Keyboard::Key::T: return "T";
            case Input::Keyboard::Key::U: return "U";
            case Input::Keyboard::Key::V: return "V";
            case Input::Keyboard::Key::W: return "W";
            case Input::Keyboard::Key::X: return "X";
            case Input::Keyboard::Key::Y: return "Y";
            case Input::Keyboard::Key::Z: return "Z";
            case Input::Keyboard::Key::Num0: return "0";
            case Input::Keyboard::Key::Num1: return "1";
            case Input::Keyboard::Key::Num2: return "2";
            case Input::Keyboard::Key::Num3: return "3";
            case Input::Keyboard::Key::Num4: return "4";
            case Input::Keyboard::Key::Num5: return "5";
            case Input::Keyboard::Key::Num6: return "6";
            case Input::Keyboard::Key::Num7: return "7";
            case Input::Keyboard::Key::Num8: return "8";
            case Input::Keyboard::Key::Num9: return "9";
            case Input::Keyboard::Key::Backspace: return "BACKSPACE";
            case Input::Keyboard::Key::Escape: return "ESCAPE";
            case Input::Keyboard::Key::Space: return "SPACE";
            case Input::Keyboard::Key::Enter: return "ENTER";
            case Input::Keyboard::Key::Tab: return "TAB";
            case Input::Keyboard::Key::Left: return "LEFT";
            case Input::Keyboard::Key::Up: return "UP";
            case Input::Keyboard::Key::Down: return "DOWN";
            case Input::Keyboard::Key::Right: return "RIGHT";
            case Input::Keyboard::Key::LShift: return "LSHIFT";
            case Input::Keyboard::Key::RShift: return "RSHIFT";
            case Input::Keyboard::Key::LControl: return "LCONTROL";
            case Input::Keyboard::Key::RControl: return "RCONTROL";
            case Input::Keyboard::Key::LAlt: return "LALT";
            case Input::Keyboard::Key::RAlt: return "RALT";

            default: return "UNKNOWN";

        }
    }

}