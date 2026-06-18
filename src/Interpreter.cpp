#include "../Novella/Syntax/NovellaScript/Interpreter.hpp"
#include "../Novella/Syntax/NovellaScript/Definition.hpp"
#include "../Novella/Input/InteractionSystem.hpp"
#include <type_traits>
#include <variant>
#include <nlohmann/json.hpp>
#include "../Novella/IO/FileReader.hpp"
#include "../Novella/Syntax/NovellaScript/Lexer.hpp"
#include "../Novella/Syntax/NovellaScript/Parser.hpp"
#include <iostream>
namespace Novella::Syntax::NovellaScript{

    void Interpreter::loadScript(const Scene::ScriptDefinition& definition){

        std::string scriptContents = IO::FileReader::getContentsFromFile(definition.path);

        std::cout << scriptContents << "\n";
        Lexer lexer(scriptContents);

        Parser parser(lexer);
        
        this->scripts.push_back(parser.parse());
    }

    std::string Interpreter::convertButtonToString(Input::Mouse::Button button){

        switch(button){

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

    std::string Interpreter::convertKeyToString(Input::Keyboard::Key key){

        switch(key){

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

            default: return "UNKOWN";

        }
    }

    void Interpreter::interpretEvent(const Event& event, CommandContext& context){

        std::visit([&](auto&& e){

            if(activeBindings.find(e.objectID) == activeBindings.end()) return;

            std::string inputString;

            if constexpr(std::is_same_v<std::decay_t<decltype(e)>, Input::ClickEvent>){

                inputString = convertButtonToString(e.button);

            }else if constexpr(std::is_same_v<std::decay_t<decltype(e)>, Input::KeyEvent>){

                inputString = convertKeyToString(e.key);
            }

            for(const auto& binding : activeBindings.at(e.objectID)){

                if(binding.triggerName == inputString){

                    evaluateExpression(*binding.callbackAction, context);
                }
            }
        }, event);
    }

    Interpreter::RunTimeValue Interpreter::callFunction(const std::string& moduleName, const std::string& functionName, const std::vector<RunTimeValue>& args){

        return RunTimeValue{};
    }
    
    void Interpreter::executeStatement(const Statement& statement){


    }

    std::string Interpreter::getFunctionName(const Expression* answer){

        //

        return std::string{};
    }
    
    Interpreter::RunTimeValue Interpreter::evaluateExpression(const Expression& expression, CommandContext& context){

        if(std::holds_alternative<FunctionCallExpression>(expression)){

            auto call = std::get<FunctionCallExpression>(expression);

            if(call.functionName == "onClick"){

                std::string targetID = std::get<VariableExpression>(call.arguments[0]).name;
                std::string triggerInput = std::get<LiteralExpression>(call.arguments[1]).value.StringValue;

                auto callbackNode = std::make_shared<FunctionCallExpression>(std::get<FunctionCallExpression>(call.arguments[2]));

                activeBindings[targetID].push_back(RuntimeBinding{triggerInput, callbackNode});

                return RunTimeValue{};

            }

            if(call.functionName == "showMessage"){

                if(!call.arguments.empty() && std::holds_alternative<LiteralExpression>(call.arguments[0])){

                    auto& message = std::get<LiteralExpression>(call.arguments[0]).value.StringValue;

                    internalCommands.execute(Alias::ShowMessage, "self", context, {{"message", message}});
                }
            }
        }

        return RunTimeValue{};
    }

    void Interpreter::resolveImports(){


    }

    void Interpreter::callInternalCommand(const std::string& name, const std::string& target, CommandContext& context, const nlohmann::json& args){

        internalCommands.execute(name, target, context, args);
    }

    void Interpreter::clear(){
        
        this->scripts.clear();        
        this->persistentStorage.clear();
        this->localScope.clear();
        this->activeBindings.clear();
    }
}