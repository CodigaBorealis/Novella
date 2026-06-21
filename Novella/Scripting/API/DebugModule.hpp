#pragma once
#include <string>

namespace Novella{

    class Logger;
}

namespace Novella::NScript{

    class DebugModule{

        public:

        DebugModule() = delete;

        DebugModule(Logger& logger)
            :
            logger(logger)
            {}
            
        void print(const std::string& message);

        private:

        Logger& logger;

    };
}