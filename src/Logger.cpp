#include "../Novella/Debug/Logger.hpp"
#include <iostream>

namespace Novella::Debug{

    void Logger::print(const std::string& message) const{

        std::cout << message << "\n";
    }

    void Logger::clearTerminal(){

        std::cout << "\033[2J\033[1;1H";

    }

    void Logger::dump(){

        while(!logs.empty()){

            std::cout << logs.top() << "\n";

            logs.pop();
        }
    }

    void Logger::reset(){

        std::stack<std::string> clean{};

        logs.swap(clean);
    }

    void Logger::storeLog(const std::string& log){

        logs.push(log);
    }
}