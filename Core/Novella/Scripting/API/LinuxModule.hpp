#pragma once
#include "../Interpreter/RuntimeContext.hpp"
#include <string>

#ifdef _WIN32

    #error "Windows-specific header cannot be included in linux build."

#endif

namespace Novella::NScript::Modules::Linux{

    std::string getUserEnv(Runtime::Context& context);
}