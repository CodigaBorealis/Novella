#pragma once
#include <string>
#include <stack>

namespace Novella::Debug{

    class Logger{

        public:

            void print(const std::string& message) const;
            void clearTerminal();
            void dump();
            void reset();
            void storeLog(const std::string& log);

        private:

        std::stack<std::string> logs;
    };
}