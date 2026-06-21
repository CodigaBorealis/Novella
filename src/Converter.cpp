#include "../Novella/Scripting/Interpreter/Converter.hpp"
#include "../Novella/Systems/Input/InputEvent.hpp"
#include <stdexcept>

namespace Novella::NScript::Runtime{


    std::string Converter::getInputFromEvent(const MouseEvent& event){

        return mouseButtonToString(event);
    }


    std::string Converter::getInputFromEvent(const KeyboardEvent& event){

        return keyboardKeyToString(event);
    }

    std::string Converter::getInputFromEvent(const InputEvent& event){

        if(std::holds_alternative<MouseEvent>(event)){

            auto& button = std::get<MouseEvent>(event);

            return mouseButtonToString(button);

        }else if(std::holds_alternative<KeyboardEvent>(event)){

            auto& key = std::get<KeyboardEvent>(event);

            return keyboardKeyToString(key);
        }

        throw std::runtime_error("Invalid input type");
    }

    std::string Converter::mouseButtonToString(const MouseEvent& event){

        switch(event.button){

            case Button::Back: return "BACK";
            case Button::Extra: return "EXTRA";
            case Button::Forward: return "FORWARD";
            case Button::Side: return "SIDE";
            case Button::Left: return "LEFT";
            case Button::Right: return "RIGHT";
            case Button::Middle: return "MIDDLE";

            default: return "UNKNOWN";
        }   
    }

    std::string Converter::keyboardKeyToString(const KeyboardEvent& event){


        switch(event.key){

            case Key::A: return "A";
            case Key::B: return "B";
            case Key::C: return "C";
            case Key::D: return "D";
            case Key::E: return "E";
            case Key::F: return "F";
            case Key::G: return "G";
            case Key::H: return "H";
            case Key::I: return "I";
            case Key::J: return "J";
            case Key::K: return "K";
            case Key::L: return "L";
            case Key::M: return "M";
            case Key::N: return "N";
            case Key::O: return "O";
            case Key::P: return "P";
            case Key::Q: return "Q";
            case Key::R: return "R";
            case Key::S: return "S";
            case Key::T: return "T";
            case Key::U: return "U";
            case Key::V: return "V";
            case Key::W: return "W";
            case Key::X: return "X";
            case Key::Y: return "Y";
            case Key::Z: return "Z";
            case Key::Num0: return "0";
            case Key::Num1: return "1";
            case Key::Num2: return "2";
            case Key::Num3: return "3";
            case Key::Num4: return "4";
            case Key::Num5: return "5";
            case Key::Num6: return "6";
            case Key::Num7: return "7";
            case Key::Num8: return "8";
            case Key::Num9: return "9";
            case Key::Backspace: return "BACKSPACE";
            case Key::Escape: return "ESCAPE";
            case Key::Space: return "SPACE";
            case Key::Enter: return "ENTER";
            case Key::Tab: return "TAB";
            case Key::Left: return "LEFT";
            case Key::Up: return "UP";
            case Key::Down: return "DOWN";
            case Key::Right: return "RIGHT";
            case Key::LShift: return "LSHIFT";
            case Key::RShift: return "RSHIFT";
            case Key::LControl: return "LCONTROL";
            case Key::RControl: return "RCONTROL";
            case Key::LAlt: return "LALT";
            case Key::RAlt: return "RALT";

            default: return "UNKNOWN";

        }
    }

}