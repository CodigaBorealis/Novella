#include "../Novella/Input/InputSystem.hpp"
#include <optional>
#include <raylib.h>

namespace Novella::Input{

    bool InputSystem::isKeyPressed(Keyboard::Key key){

        return ::IsKeyPressed(static_cast<int>(key));
    }

    bool InputSystem::isKeyDown(Keyboard::Key key){

        return ::IsKeyDown(static_cast<int>(key));
    }

    bool InputSystem::isKeyReleased(Keyboard::Key key){

        return ::IsKeyReleased(static_cast<int>(key));
    }

    bool InputSystem::isKeyUp(Keyboard::Key key){

        return ::IsKeyUp(static_cast<int>(key));

    }

    Keyboard::Key getKeyPressed(){

        return Keyboard::Key(::GetKeyPressed());
    }

    char getCharPressed(){

        return ::GetCharPressed();
    }

    bool InputSystem::isMouseButtonPressed(Mouse::Button button){

        return ::IsMouseButtonPressed(static_cast<int>(button));
    }

    bool InputSystem::isMouseButtonDown(Mouse::Button button){

        return ::IsMouseButtonDown(static_cast<int>(button));
    }

    bool InputSystem::isMouseButtonReleased(Mouse::Button button){

        return ::IsMouseButtonReleased(static_cast<int>(button));
    }

    bool InputSystem::isMouseButtonUp(Mouse::Button button){

        return ::IsMouseButtonUp(static_cast<int>(button));
    }
    
    float InputSystem::getMouseX(){

        return ::GetMouseX();
    }

    float InputSystem::getMouseY(){

        return ::GetMouseY();
    }

    void InputSystem::setMousePosition(const Math::Vector2f& position){

        ::SetMousePosition(position.x, position.y);
    }

    Math::Vector2f InputSystem::mousePosition(){

        return ::GetMousePosition();
    }

    Math::Vector2f InputSystem::mouseDelta(){

        return ::GetMouseDelta();
    }

    float InputSystem::getMouseWheelMove(){

        return ::GetMouseWheelMove();
    }

    Math::Vector2f InputSystem::getMouseWheelMoveV(){

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

    std::optional<Mouse::Button> InputSystem::getMouseButtonPressed(){

        for(int x = 0; x <= ::MOUSE_BUTTON_BACK; ++x){

            if(::IsMouseButtonPressed(x)){

                return Mouse::Button(x);
            }
        }

        return std::nullopt;
    }

    std::optional<Keyboard::Key> InputSystem::getKeyboardKeyPressed(){

        for(int x = 0; x <= ::KEY_KB_MENU; ++x){

            if(::IsKeyPressed(x)){

                return Keyboard::Key(x);
            }
        }

        return std::nullopt;
    }


}