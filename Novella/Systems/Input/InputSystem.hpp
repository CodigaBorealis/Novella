#pragma once
#include "InputTypes.hpp"
#include "../../Core/Math/Vector2x.hpp"
#include <optional>

namespace Novella{

    class InputSystem{

    public:

    InputSystem() = default;
                    
    InputSystem(const InputSystem&) = delete;

    InputSystem& operator=(const InputSystem&) = delete;

    InputSystem(InputSystem&&) = delete;
    
    InputSystem& operator=(InputSystem&&) = delete;

    static bool isKeyPressed(Key key);
    static bool isKeyDown(Key key);
    static bool isKeyReleased(Key key);
    static bool isKeyUp(Key key);

    static Key getKeyPressed();
    static char getCharPressed();

    static bool isMouseButtonPressed(Button button);
    static bool isMouseButtonDown(Button button);
    static bool isMouseButtonReleased(Button button);
    static bool isMouseButtonUp(Button button);
    
    static float getMouseX();
    static float getMouseY();
    static void setMousePosition(const Vector2f& position);

    static Vector2f mousePosition();
    static Vector2f mouseDelta();

    static float getMouseWheelMove();
    static Vector2f getMouseWheelMoveV();

    static void showCursor();
    static void hideCursor();
    static void enableCursor();
    static void disableCursor();
    static bool isCursorHidden();
    static bool isCursorOnScreen();

    static std::optional<Button> getMouseButtonPressed();
    static std::optional<Key> getKeyboardKeyPressed();

    inline Key fromRaylib(int key){

        switch(key){

            #define X(name, raylib) case raylib: return Key::name;
            #include "Keys.hpp"
            #undef X

            default:

                return Key::A;
        }
    }

    inline int toRaylib(Key key){

        switch(key){

            #define X(name, raylib) case Key::name: return raylib;
            #include "Keys.hpp"
            #undef X

            default:

                return KEY_NULL;
        }
    }

    inline bool isPressed(Key key){

        return ::IsKeyDown(toRaylib(key));
    }
};

    inline Button fromRaylib(int button){

        switch(button){
            
            #define X(name, raylib) case raylib: return Button::name;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return Button::Left;
        }
    }

    inline int toRaylib(Button button){

        switch (button) {
            
            #define X(name, raylib) case Button::name: return raylib;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return MOUSE_BUTTON_LEFT;
        }
    }

    inline bool isPressed(Button button){return ::IsMouseButtonDown(toRaylib(button));}

}
