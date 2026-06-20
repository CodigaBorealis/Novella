#pragma once
#include <string>

namespace Novella::Debug{

    class Logger;
}

namespace Novella::Syntax::NovellaScript::API{

    class DebugModule{

        public:

        DebugModule() = delete;

        DebugModule(Debug::Logger& logger)
            :
            logger(logger)
            {}
            
        void print(const std::string& message);

        private:

        Debug::Logger& logger;

    };
}