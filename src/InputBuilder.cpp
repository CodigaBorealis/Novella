#include "../Novella/IO/InputBuilder.hpp"
#include "../Novella/Input/Mouse.hpp"
#include "../Novella/Input/Keyboard.hpp"
#include <stdexcept>
//#include <unordered_map>
//#include "../Novella/Syntax/Scene/SceneDefinition.hpp"
#include "../Novella/Engine.hpp"

namespace Novella::SceneLoader{

    void InputBuilder::buildInput(Engine &engine, const Syntax::Scene::InputBindingDefinition &input){
/*
        std::unordered_map<std::string, std::string> args;

        if(!input.targetName.empty()){

            args["id"] = input.targetName;

        }

        if(input.inputType == "click"){

            engine.input().addClickBinding(input.targetName, getMouseButton(input.input), input.commandAlias, args);

            return;

        }else if(input.inputType == "key"){

            engine.input().addKeyBinding(input.targetName, getKeyboardKey(input.input), input.commandAlias, args);

            return;
        }

        throw std::runtime_error("Invalid input type '" + input.inputType + "'");

    */
    }

    Input::Mouse::Button InputBuilder::getMouseButton(const std::string& button){

        if(button == "Left") return Input::Mouse::Button::Left;
        
        if(button == "Right") return Input::Mouse::Button::Right;

        if(button == "Middle") return Input::Mouse::Button::Middle;

        if(button == "Side") return Input::Mouse::Button::Side;

        if(button == "Extra") return Input::Mouse::Button::Extra;

        if(button == "Forward") return Input::Mouse::Button::Forward;

        if(button == "Back") return Input::Mouse::Button::Back;

        throw std::runtime_error("Invalid value for mouse button: '" + button + "'");

    }

    Input::Keyboard::Key InputBuilder::getKeyboardKey(const std::string& key){

        if(key.size() == 1 && key[0] >= 'A' && key[0] <= 'Z'){

            return static_cast<Input::Keyboard::Key>(static_cast<int>(Input::Keyboard::Key::A) + key[0] - 'A');
        }

        if(key == "Num0") return Input::Keyboard::Key::Num0;

        if(key == "Num1") return Input::Keyboard::Key::Num1;

        if(key == "Num2") return Input::Keyboard::Key::Num2;

        if(key == "Num3") return Input::Keyboard::Key::Num3;

        if(key == "Num4") return Input::Keyboard::Key::Num4;

        if(key == "Num5") return Input::Keyboard::Key::Num5;

        if(key == "Num6") return Input::Keyboard::Key::Num6;

        if(key == "Num7") return Input::Keyboard::Key::Num7;

        if(key == "Num8") return Input::Keyboard::Key::Num8;

        if(key == "Num9") return Input::Keyboard::Key::Num9;

        if(key == "Escape") return Input::Keyboard::Key::Escape;

        if(key == "Space") return Input::Keyboard::Key::Space;

        if(key == "Enter") return Input::Keyboard::Key::Enter;

        if(key == "Backspace") return Input::Keyboard::Key::Backspace;

        if(key == "Tab") return Input::Keyboard::Key::Tab;

        if(key == "Left") return Input::Keyboard::Key::Left;

        if(key == "Right") return Input::Keyboard::Key::Right;

        if(key == "Up") return Input::Keyboard::Key::Up;

        if(key == "Down") return Input::Keyboard::Key::Down;

        if(key == "LShift") return Input::Keyboard::Key::LShift;

        if(key == "RShift") return Input::Keyboard::Key::RShift;
        
        if(key == "LControl") return Input::Keyboard::Key::LControl;

        if(key == "RControl") return Input::Keyboard::Key::RControl;

        if(key == "LAlt") return Input::Keyboard::Key::LAlt;

        if(key == "RAlt") return Input::Keyboard::Key::RAlt;

        throw std::runtime_error("Invalid value for keyboard key: '" + key + "'");

    }

}