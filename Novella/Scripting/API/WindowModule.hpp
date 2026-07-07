#pragma once
#include <string>
#include "../../Core/Math/Vector2x.hpp"
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class Window;
}
//The Value variant used by the scripting language treats all numbers as double

namespace Novella::NScript::Modules::Window{
    
    void center(Runtime::Context& context);
    void close(Runtime::Context& context);
    void minimize(Runtime::Context& context);
    void maximize(Runtime::Context& context);

    bool isFullScreen(Runtime::Context& context);
    bool isResizable(Runtime::Context& context);
    bool isFocused(Runtime::Context& context);
    
    void setTitle(Runtime::Context& context, const std::string& title);

    void setPositionX(Runtime::Context& context, double value);
    void setPositionY(Runtime::Context& context, double value);
    void setPosition(Runtime::Context& context, double x, double y);

    void setWidth(Runtime::Context& context, double width);
    void setHeight(Runtime::Context& context, double height);
    void setSize(Runtime::Context& context, double width, double height);

    void setIcon(Runtime::Context& context, const std::string& resource);
        
    double getWidth(Runtime::Context& context);

    double getHeight(Runtime::Context& context);

    double getPositionX(Runtime::Context& context);

    double getPositionY(Runtime::Context& context);

    std::string getTitle(Runtime::Context& context);

};
