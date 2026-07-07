#pragma once
#include "../../Systems/Input/InputSystem.hpp"
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class InteractionSystem;
}

namespace Novella::NScript::Modules::Input{

    void setCursotVisible(Runtime::Context& context, bool val);
    void lockCursor(Runtime::Context& context, bool val);
    void setCursorPosition(Runtime::Context& context, double x, double y);
    void moveCursor(Runtime::Context& context, double deltaX, double deltaY);

    bool isKeyDown(Runtime::Context& context, const std::string& key);
    bool isKeyPressed(Runtime::Context& context, const std::string& key);
    bool isKeyReleased(Runtime::Context& context, const std::string& key);
    bool isKeyUp(Runtime::Context& context, const std::string& key);
    
    bool isMouseDown(Runtime::Context& context, const std::string& button);
    bool isMousePressed(Runtime::Context& context, const std::string& button);
    bool isMouseUp(Runtime::Context& context, const std::string& button);
    bool isMouseReleased(Runtime::Context& context, const std::string& button);
    
    double getMouseX(Runtime::Context& context);
    double getMouseY(Runtime::Context& context);

};
