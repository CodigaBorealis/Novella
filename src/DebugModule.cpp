#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Core/Debug/Logger.hpp"

namespace Novella::NScript::Modules::Debug{

    void print(Runtime::Context& context, const std::string& message){

        context.logger->print(message);
    }
}