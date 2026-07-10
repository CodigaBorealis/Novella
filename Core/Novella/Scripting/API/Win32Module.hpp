#pragma once
#include "../Interpreter/RuntimeContext.hpp"
#include <string>

#ifdef __linux_//For now i leave it like this to shut up clangd

    #error "Windows-specific header cannot be included in linux build."

#endif

namespace Novella::NScript::Modules::Win32{

    std::string getUserEnv(Runtime::Context& context);

}