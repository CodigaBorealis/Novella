#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"

namespace Novella{

    class SceneManager;
}

namespace Novella::NScript::Modules::Scene{

    void load(Runtime::Context& context,const std::string& name);

    void reload(Runtime::Context& context);

    double objectCount(Runtime::Context& context);

    std::string name(Runtime::Context& context);

    std::string path(Runtime::Context& context);

};   
