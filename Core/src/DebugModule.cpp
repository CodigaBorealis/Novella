#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Core/Debug/Logger.hpp"
#include <cstdlib>

namespace Novella::NScript::Modules::Debug{

    void print(Runtime::Context& context, const std::string& message){

        context.logger->print(message);
    }

    void clear(Runtime::Context& context){

        #ifdef _WIN32
        
        std::system("cls");

        #endif

        #ifdef __linux__

        std::system("clear");
        #endif

        
    }
}