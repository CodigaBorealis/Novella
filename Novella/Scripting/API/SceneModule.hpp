#pragma once
#include <cstdint>
#include <string>
#include "../../Core/Math/Vector2x.hpp"
#include "../../Scene/Handle.hpp"
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class SceneManager;
}

namespace Novella::NScript::Modules::Scene{


    const Handle& getHandle(Runtime::Context& context, const std::string& name);

    void destroy(Runtime::Context& context, const Handle& handle);

    void setPosition(Runtime::Context& context, const Handle& handle, Vector2d& position);


};   
