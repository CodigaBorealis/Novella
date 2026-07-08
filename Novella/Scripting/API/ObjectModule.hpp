#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
#include "../../Scene/Handle.hpp"

namespace Novella::NScript::Modules::Object{

    Handle get(Runtime::Context& context, const std::string& name);

    void destroy(Runtime::Context& context, Handle handle);

    bool exists(Runtime::Context& context, Handle handle);

    std::string getName(Runtime::Context& context, Handle handle);
}