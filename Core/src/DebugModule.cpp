#include "Novella/Scripting/API/DebugModule.hpp"
#include <cstdlib>
#include <iostream>

namespace Novella::NScript::Modules::Debug{

    void print(Runtime::Context& context, const std::string& message){

        std::cout << message << "\n";
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