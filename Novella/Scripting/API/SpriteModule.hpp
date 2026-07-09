#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"
namespace Novella::NScript::Modules::Sprite{

    void setTexture(Runtime::Context& context, Handle handle, const std::string& name);
    void setTint(Runtime::Context& context, Handle handle, double r, double g, double b, double a);
    std::string getTexture(Runtime::Context& context, Handle handle);

}