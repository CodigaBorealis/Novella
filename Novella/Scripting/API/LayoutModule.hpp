#pragma once

namespace Novella{

    class LayoutSystem;
}

namespace Novella::NScript{

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