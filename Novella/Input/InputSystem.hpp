#pragma once
#include "Keyboard.hpp"
#include "../Math/Vector2x.hpp"
#include "Mouse.hpp"

namespace Novella::Input {

    class InputSystem{

    public:

    InputSystem() = default;
                    
    InputSystem(const InputSystem&) = delete;

    InputSystem& operator=(const InputSystem&) = delete;

    InputSystem(InputSystem&&) = delete;
    
    InputSystem& operator=(InputSystem&&) = delete;

    static bool isKeyPressed(Keyboard::Key key);
    static bool isKeyDown(Keyboard::Key key);
    static bool isKeyReleased(Keyboard::Key key);
    static bool isKeyUp(Keyboard::Key key);

    static Keyboard::Key getKeyPressed();
    static char getCharPressed();

    static bool isMouseButtonPressed(Mouse::Button button);
    static bool isMouseButtonDown(Mouse::Button button);
    static bool isMouseButtonReleased(Mouse::Button button);
    static bool isMouseButtonUp(Mouse::Button button);
    
    static float getMouseX();
    static float getMouseY();
    static void setMousePosition(const Math::Vector2f& position);

    static Math::Vector2f mousePosition();
    static Math::Vector2f mouseDelta();

    static float getMouseWheelMove();
    static Math::Vector2f getMouseWheelMoveV();

    static void showCursor();
    static void hideCursor();
    static void enableCursor();
    static void disableCursor();
    static bool isCursorHidden();
    static bool isCursorOnScreen();

};
}
