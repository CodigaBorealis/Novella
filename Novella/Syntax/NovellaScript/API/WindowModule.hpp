#pragma once
#include <string>

namespace Novella{

    class Window;
}

namespace Novella::Syntax::NovellaScript::API{

    class WindowModule{

        public:
            
        WindowModule() = delete;

        WindowModule(Window& window)
            :
            window(window)
            {}
            
        private:

        Window& window;
    };
}