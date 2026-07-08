#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"
namespace Novella::NScript::Modules::Sprite{

    void setTexture(Runtime::Context& context, Handle handle, const std::string& name);
    void setTint(Runtime::Context& context, Handle handle, const std::string& name);
    std::string getTexture(Runtime::Context& context, Handle handle);

}