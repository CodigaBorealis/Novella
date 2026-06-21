#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Core/Debug/Logger.hpp"

namespace Novella::NScript{

    void DebugModule::print(const std::string& message){

        logger.print(message);
    }
}