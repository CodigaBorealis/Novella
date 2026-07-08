#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"

namespace Novella::NScript::Modules::Layout {

    void setStyle(Runtime::Context& context, Handle handle, const std::string& style);
    void setWidth(Runtime::Context& context, Handle handle, double width);
    void setHeight(Runtime::Context& context, Handle handle, double height);
    void setSize(Runtime::Context& context, Handle handle, double width, double height);

    double getWidth(Runtime::Context& context, Handle handle);
    double getHeight(Runtime::Context& context, Handle handle);
}