#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"
namespace Novella::NScript::Modules::Text {

    void setText(Runtime::Context& context, Handle handle, const std::string& text);
    std::string getText(Runtime::Context& context, Handle handle);
    void setFont(Runtime::Context& context, Handle handle, const std::string& name);
    void setFontSize(Runtime::Context& context, Handle handle, double size);
    void setFontColor(Runtime::Context& context, Handle handle, double r, double g, double b, double a);
    std::string getFont(Runtime::Context& context, Handle handle);
    double getFontSize(Runtime::Context& context, Handle handle);
}