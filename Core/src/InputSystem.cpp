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

        ::SetMousePosition(static_cast<int>(position.x), static_cast<int>(position.y));
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

    void InputSystem::setCursorType(CursorType type){

        switch (type){
        
            case CursorType::Default:
            
                ::SetMouseCursor(MOUSE_CURSOR_DEFAULT);

                return;

            case CursorType::Arrow:
            
                ::SetMouseCursor(MOUSE_CURSOR_ARROW);

                return;            

            case CursorType::Crosshair:
            
                ::SetMouseCursor(MOUSE_CURSOR_CROSSHAIR);

                return; 
        
            case CursorType::Hand:
            
                ::SetMouseCursor(MOUSE_CURSOR_POINTING_HAND);

                return;

            case CursorType::Ibeam:

                ::SetMouseCursor(MOUSE_CURSOR_IBEAM);
                return;

            case CursorType::NotAllowed:

                ::SetMouseCursor(MOUSE_CURSOR_NOT_ALLOWED);

                return;
        }   
    }
}