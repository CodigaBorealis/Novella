#include "../Novella/Systems/Input/InputSystem.hpp"
#include <optional>
#include <raylib.h>
namespace Novella{
    
    float InputSystem::getMouseX(){

        return ::GetMouseX();
    }

    float InputSystem::getMouseY(){

        return ::GetMouseY();
    }

    void InputSystem::setMousePosition(const Vector2f& position){

        ::SetMousePosition(position.x, position.y);
    }

    Vector2f InputSystem::mousePosition(){

        return ::GetMousePosition();
    }

    Vector2f InputSystem::mouseDelta(){

        return ::GetMouseDelta();
    }

    float InputSystem::getMouseWheelMove(){

        return ::GetMouseWheelMove();
    }

    Vector2f InputSystem::getMouseWheelMoveV(){

        return ::GetMouseWheelMoveV();
    }

    void InputSystem::showCursor(){

        ::ShowCursor();
    }

    void InputSystem::hideCursor(){

        ::HideCursor();
    }

    void InputSystem::enableCursor(){

        ::EnableCursor();
    }

    void InputSystem::disableCursor(){

        ::DisableCursor();
    }

    bool InputSystem::isCursorHidden(){

        return ::IsCursorHidden();
    }

    bool InputSystem::isCursorOnScreen(){

        return ::IsCursorOnScreen();
    }

    std::optional<Button> InputSystem::getMouseButtonPressed(){

        for(int x = 0; x < ::MOUSE_BUTTON_BACK; x++){

            if(::IsMouseButtonPressed(x)){

                return Button(x);
            }
        }

        return std::nullopt;
    }

    std::optional<Key> InputSystem::getKeyboardKeyPressed(){

        for(int x = 0; x < ::KEY_KB_MENU; x++){

            if(::IsKeyPressed(x)){

                return Key(x);
            }
        }

        return std::nullopt;
    }


}