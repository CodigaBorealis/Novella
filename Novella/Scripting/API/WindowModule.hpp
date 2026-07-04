#pragma once
#include <string>
#include "../../Core/Math/Vector2x.hpp"
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class Window;
}

namespace Novella::NScript::Modules{
        
    void setTitle(Runtime::Context& context, const std::string& title);

    void setPosition(Runtime::Context& context, const Vector2i& position);

    void move(Runtime::Context& context, const Vector2i& delta);

    void setSize(Runtime::Context& context, const Vector2i& dimensions);

    void resize(Runtime::Context& context, const Vector2i& delta);

    void setIcon(Runtime::Context& context, const std::string& resource);
        
    Vector2i getSize(Runtime::Context&);

    Vector2i getPosition(Runtime::Context&);

    std::string getTitle(Runtime::Context&);

};
