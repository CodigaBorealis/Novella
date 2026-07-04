#pragma once
#include <string>
#include "../../Core/Math/Vector2x.hpp"
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class Window;
}
//The Value variant used by the scripting language treats all numbers as double

namespace Novella::NScript::Modules::Window{
        
    void setTitle(Runtime::Context& context, const std::string& title);

    void setPositionX(Runtime::Context& context, double value);

    void setPositionY(Runtime::Context& context, double value);

    void setWidth(Runtime::Context& context, double width);

    void setHeight(Runtime::Context& context, double height);

    void setIcon(Runtime::Context& context, const std::string& resource);
        
    double getWidth(Runtime::Context&);

    double getHeight(Runtime::Context&);

    double getPositionX(Runtime::Context&);

    double getPositionY(Runtime::Context&);

    std::string getTitle(Runtime::Context&);

};
