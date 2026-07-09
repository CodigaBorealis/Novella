#pragma once
#include "InputTypes.hpp"
#include "../../Core/Math/Vector2x.hpp"
#include <optional>
#include <raylib.h>

namespace Novella{

    class InputSystem{

    public:

    InputSystem() = default;
                    
    InputSystem(const InputSystem&) = delete;

    InputSystem& operator=(const InputSystem&) = delete;

    InputSystem(InputSystem&&) = delete;
    
    InputSystem& operator=(InputSystem&&) = delete;

    static Key getKeyPressed();
    static char getCharPressed();
    
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

    static inline Key keyFromRaylib(int key){

        switch(key){

            #define X(name, raylib) case raylib: return Key::name;
            #include "Keys.hpp"
            #undef X

            default:

                return Key::A;
        }
    }

    static inline int toRaylib(Key key){

        switch(key){

            #define X(name, raylib) case Key::name: return raylib;
            #include "Keys.hpp"
            #undef X

            default:

                return KEY_NULL;
        }
    }

    static inline bool isUp(Key key){

        return ::IsKeyUp(toRaylib(key));
    }
    
    static inline bool isDown(Key key){

        return ::IsKeyDown(toRaylib(key));
    }
    
    static inline bool isPressed(Key key){

        return ::IsKeyPressed(toRaylib(key));
    }    
    
    static inline bool isReleased(Key key){

        return ::IsKeyReleased(toRaylib(key));
    }

    static inline Button buttonFromRaylib(int button){

        switch(button){
            
            #define X(name, raylib) case raylib: return Button::name;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return Button::Left;
        }
    }

    static inline int toRaylib(Button button){

        switch (button) {
            
            #define X(name, raylib) case Button::name: return raylib;
            #include "MouseButtons.hpp"
            #undef X

            default:

                return MOUSE_BUTTON_LEFT;
        }
    }

    static inline bool isUp(Button button){

        return ::IsMouseButtonUp(toRaylib(button));
    }
    
    static inline bool isDown(Button button){

        return ::IsMouseButtonDown(toRaylib(button));
    }
    
    static inline bool isPressed(Button button){

        return ::IsMouseButtonPressed(toRaylib(button));
    }    

    static inline bool isReleased(Button button){

        return ::IsMouseButtonReleased(toRaylib(button));
    }    

};
}
