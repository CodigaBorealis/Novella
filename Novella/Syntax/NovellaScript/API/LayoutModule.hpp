#pragma once

namespace Novella{

    class LayoutSystem;
}

namespace Novella::Syntax::NovellaScript::API{

    class LayoutModule{
            
        public:

        LayoutModule() = delete;

        LayoutModule(LayoutSystem& layout)
            :
            layout(layout)
            {}
            
        private:

        LayoutSystem& layout;
    };
}