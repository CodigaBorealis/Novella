#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
namespace Novella{

    class Logger;
}

namespace Novella::NScript::Runtime{

    class RuntimeEnvironment;
}

namespace Novella::NScript::Modules::Debug{

    void print(Runtime::Context& context, const std::string& message);
        
    void clear(Runtime::Context& context);

    void registerModule(Runtime::RuntimeEnvironment& runtime);

};
