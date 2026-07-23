#include "../Novella/Scripting/API/InputModule.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Systems/Input/InputSystem.hpp"
#include "../Novella/Components/Traits/Layoutable.hpp"
#include "../Novella/Components/Traits/Clickable.hpp"
#include "../Novella/Windowing/Window.hpp"
#include "../Novella/Scene/SceneManager.hpp"
#include "../Novella/Utils/String.hpp"
#include <stdexcept>
#include <string>
namespace Novella::NScript::Modules::Input{

    void setCursorVisible(Runtime::Context& context, bool val){

        if(!val) InputSystem::hideCursor();

        InputSystem::showCursor();
    }

    void lockCursor(Runtime::Context& context, bool val){

        if(!val) InputSystem::enableCursor();

        InputSystem::disableCursor();
    }

    void setCursorPosition(Runtime::Context& context, double x, double y){

        if(x < 0 || y < 0) throw std::runtime_error("setCursorPosition: cannot set cursor position to a negative value");

        InputSystem::setMousePosition({static_cast<float>(x), static_cast<float>(y)});
    }

    void moveCursor(Runtime::Context& context, double deltaX, double deltaY){

        float afterDeltaX = InputSystem::getMouseX() + deltaX;
        float afterDeltaY = InputSystem::getMouseY() + deltaY;

        if(afterDeltaX < 0) afterDeltaX = 0;
        if(afterDeltaY < 0) afterDeltaY = 0;

        auto windowSize = context.window->getSize();

        if(afterDeltaX > windowSize.x) afterDeltaX = windowSize.x;
        if(afterDeltaY > windowSize.y) afterDeltaY = windowSize.y;

        InputSystem::setMousePosition({afterDeltaX, afterDeltaY});
    }

    bool isKeyUp(Runtime::Context& context, const std::string& key){

        std::string sanitized = Utils::String::trim(Utils::String::toUpper(key));
        
        return InputSystem::isUp(getKey(sanitized));
    }

    bool isKeyDown(Runtime::Context& context, const std::string& key){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(key));

        return InputSystem::isDown(getKey(sanitized));
    }

    bool isKeyPressed(Runtime::Context& context, const std::string& key){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(key));

        return InputSystem::isPressed(getKey(sanitized));
    }

    bool isKeyReleased(Runtime::Context& context, const std::string& key){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(key));

        return InputSystem::isReleased(getKey(sanitized));
    }

    bool isMouseDown(Runtime::Context& context, const std::string& button){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(button));

        return InputSystem::isDown(getButton(sanitized));
    }

    bool isMousePressed(Runtime::Context& context, const std::string& button){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(button));

        return InputSystem::isPressed(getButton(sanitized));
    }

    bool isMouseUp(Runtime::Context& context, const std::string& button){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(button));

        return InputSystem::isUp(getButton(button));
    }
    
    bool isMouseReleased(Runtime::Context& context, const std::string& button){
        
        std::string sanitized = Utils::String::trim(Utils::String::toUpper(button));

        return InputSystem::isReleased(getButton(button));
    }

    double getMouseX(Runtime::Context& context){

        return InputSystem::getMouseX();
    }

    double getMouseY(Runtime::Context& context){

        return InputSystem::getMouseY();
    }
    
    //This 'works' in the sense that it works just fine in traditional non tiling window managers
    //It breaks on niri but works just fine if you just increase your window size until it uses the
    //entire mosaic
         
    bool isMouseOver(Runtime::Context& context, Handle handle){

        if(handle.generation == 0) return false;
        
        auto* currentScene = context.scene->getCurrentScene();

        if(!currentScene){

            Debug::print(context, "NovellaScript : Input.isMouseOver() requires a scene to exist in order to query");

            return false;
        }
        
        auto* clickable = currentScene->getInterface<Traits::Clickable>(handle);

        if(!clickable) return false;

        auto* layoutable = currentScene->getInterface<Traits::Layoutable>(handle);
        
        if(!layoutable) return false;

        Vector2f rawMouse = {InputSystem::getMouseX(), InputSystem::getMouseY()};
        Vector2f virtualMouse = context.renderer->toVirtualCoordinates(rawMouse);
        
        const auto& rect = layoutable->getComputedRectangle();

        return (virtualMouse.x >= rect.x && virtualMouse.x <= rect.x + rect.width && virtualMouse.y >= rect.y && virtualMouse.y <= rect.y + rect.height);
    }

    bool isObjectClicked(Runtime::Context& context, Handle handle, const std::string& button){

        if(!isMouseOver(context, handle)) return false;

        return isMousePressed(context, button);
    }

    void setCursorType(Runtime::Context &context, const std::string &string){

        std::string sanitized = Utils::String::toUpper(Utils::String::trim(string));

        if(sanitized == "DEFAULT"){

            InputSystem::setCursorType(InputSystem::CursorType::Default);

            return;

        }else if(sanitized == "ARROW"){

            InputSystem::setCursorType(InputSystem::CursorType::Arrow);

            return;

        }else if(sanitized == "HAND"){

            InputSystem::setCursorType(InputSystem::CursorType::Hand);
            
            return;

        }else if(sanitized == "CROSSHAIR"){

            InputSystem::setCursorType(InputSystem::CursorType::Crosshair);
            
            return;

        }else if(sanitized == "IBEAM"){

            InputSystem::setCursorType(InputSystem::CursorType::Ibeam);
            
        }else if(sanitized == "NOTALLOWED"){

            InputSystem::setCursorType(InputSystem::CursorType::NotAllowed);
            
            return;
        }

        throw std::runtime_error("NovellaScript Runtime Error: Unknown cursor type '" + sanitized + "'");
    }

    std::string getKeyPressed(Runtime::Context& context){

        auto key = InputSystem::getKeyboardKeyPressed();

        if(!key) return "";

        return toString(key.value());

    }

    std::string getButtonPressed(Runtime::Context& context){

        auto button = InputSystem::getMouseButtonPressed();

        if(!button) return "";

        return toString(button.value());
    }

}