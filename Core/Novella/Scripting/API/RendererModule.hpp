#pragma once
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"
#include <raylib.h>

namespace Novella{

    class Renderer;
}

namespace Novella::NScript::Modules::Renderer{
    
    void setBackgroundColor(Runtime::Context& context, double r, double g, double b, double a);
}