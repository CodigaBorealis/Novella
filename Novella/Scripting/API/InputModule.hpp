#pragma once

namespace Novella{

    class InteractionSystem;
}

namespace Novella::NScript{

    class InputModule{

        public:

        InputModule() = delete;

        InputModule(InteractionSystem& input)
            :
            input(input)
            {}

        private:

        InteractionSystem& input;    

    };
}