#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include <optional>
#include <raylib.h>
#include <string>
#include "../Renderer/Renderer.hpp"
namespace Novella{

    enum class Button{

        #define X(name, raylib) name,
        #include "MouseButtons.hpp"
        #undef X
    };
    
    enum class Key{

        #define X(name, raylib) name,
        #include "Keys.hpp"
        #undef X

    };

    static constexpr std::string toString(Key key){

        if (key >= Key::A && key <= Key::Z){

            static constexpr std::string letters[] = {"A","B","C","D","E","F","G","H","I","J","K","L","M",
                "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
            };

            return letters[static_cast<int>(key) - static_cast<int>(Key::A)];
        }

        switch (key){

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
            case Key::Escape:   return "ESCAPE";
            case Key::Space:    return "SPACE";
            case Key::Enter:    return "ENTER";
            case Key::Backspace:return "BACKSPACE";
            case Key::Tab:      return "TAB";
            case Key::Left:     return "LEFT";
            case Key::Right:    return "RIGHT";
            case Key::Up:       return "UP";
            case Key::Down:     return "DOWN";
            case Key::LShift:   return "LSHIFT";
            case Key::RShift:   return "RSHIFT";
            case Key::LControl: return "LCONTROL";
            case Key::RControl: return "RCONTROL";
            case Key::LAlt:     return "LALT";
            case Key::RAlt:     return "RALT";

            default:

            return "UNKOWN";
        }
    }

    static constexpr Key getKey(const std::string& stringRepresentation){

    if(stringRepresentation.size() == 1 && stringRepresentation[0] >= 'A' && stringRepresentation[0] <= 'Z'){

            return static_cast<Key>(static_cast<int>(Key::A) + stringRepresentation[0] - 'A');
        }

        if(stringRepresentation == "0") return Key::Num0;

        if(stringRepresentation == "1") return Key::Num1;

        if(stringRepresentation == "2") return Key::Num2;

        if(stringRepresentation == "3") return Key::Num3;

        if(stringRepresentation == "4") return Key::Num4;

        if(stringRepresentation == "5") return Key::Num5;

        if(stringRepresentation == "6") return Key::Num6;

        if(stringRepresentation == "7") return Key::Num7;

        if(stringRepresentation == "8") return Key::Num8;

        if(stringRepresentation == "9") return Key::Num9;

        if(stringRepresentation == "ESCAPE") return Key::Escape;

        if(stringRepresentation == "SPACE") return Key::Space;

        if(stringRepresentation == "ENTER") return Key::Enter;

        if(stringRepresentation == "BACKSPACE") return Key::Backspace;

        if(stringRepresentation == "TAB") return Key::Tab;

        if(stringRepresentation == "LEFT") return Key::Left;

        if(stringRepresentation == "RIGHT") return Key::Right;

        if(stringRepresentation == "UP") return Key::Up;

        if(stringRepresentation == "DOWN") return Key::Down;

        if(stringRepresentation == "LSHIFT") return Key::LShift;

        if(stringRepresentation == "RSHIFT") return Key::RShift;
        
        if(stringRepresentation == "LCONTROL") return Key::LControl;

        if(stringRepresentation == "RCONTROL") return Key::RControl;

        if(stringRepresentation == "LALT") return Key::LAlt;

        if(stringRepresentation == "RALT") return Key::RAlt;

        return Key::A;

    }

    static constexpr Button getButton(const std::string& stringRepresentation){

        if(stringRepresentation == "LEFT") return Button::Left;
        
        if(stringRepresentation == "RIGHT") return Button::Right;

        if(stringRepresentation == "MIDDLE") return Button::Middle;

        if(stringRepresentation == "SIDE") return Button::Side;

        if(stringRepresentation == "EXTRA") return Button::Extra;

        if(stringRepresentation == "FORWARD") return Button::Forward;

        if(stringRepresentation == "BACK") return Button::Back;

        return  Button::Left;
    }

    static constexpr std::string toString(Button button){

        switch(button){

            case Button::Left: return "LEFT";
            case Button::Middle: return "MIDDLE";
            case Button::Right: return "RIGHT";
            case Button::Side: return "SIDE";
            case Button::Extra: return "EXTRA";
            case Button::Forward: return "FORWARD";
            case Button::Back: return "BACK";
        }

        return "UNKOWN";
    }


    class InputSystem{

    public:

    InputSystem() = default;
                    
    InputSystem(const InputSystem&) = delete;

    InputSystem& operator=(const InputSystem&) = delete;

    InputSystem(InputSystem&&) = delete;
    
    InputSystem& operator=(InputSystem&&) = delete;

    static Vector2f getVirtualMousePosition(const Renderer& renderer);

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

    enum class CursorType : short{

        Default,
        Arrow,
        Hand,
        Crosshair,
        Ibeam,
        NotAllowed
        
    };

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

    static void setCursorType(CursorType type);
};
}
