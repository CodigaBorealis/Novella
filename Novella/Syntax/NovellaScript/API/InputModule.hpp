#pragma once

namespace Novella::Input{

    class InteractionSystem;
}

namespace Novella::Syntax::NovellaScript::API{

    class InputModule{

        public:

        InputModule() = delete;

        InputModule(Input::InteractionSystem& input)
            :
            input(input)
            {}

        private:

        Input::InteractionSystem& input;    

    };
}