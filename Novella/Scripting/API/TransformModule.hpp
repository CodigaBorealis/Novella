#pragma once
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"

namespace Novella::NScript::Modules::Transform{
    
    void setRotation(Runtime::Context& context, Handle handle, double degrees);
    void rotate(Runtime::Context& context, Handle handle,double delta);
    void flipX(Runtime::Context& context, Handle handle);
    void flipY(Runtime::Context& context, Handle handle);

    void setPosition(Runtime::Context& context, Handle handle, double x, double y);
    void setPositionX(Runtime::Context& context, Handle handle, double x);
    void setPositionY(Runtime::Context& context, Handle handle, double y);
    void move(Runtime::Context& context, Handle handle, double deltaX, double deltaY);

    double getX(Runtime::Context& context, Handle handle);
    double getY(Runtime::Context& context, Handle handle);

    double getRotation(Runtime::Context& context, Handle handle);
}