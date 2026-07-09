#pragma once

namespace Novella::Traits{

    struct Interactable{
        
        virtual ~Interactable() = default;
        
        bool acceptsKeyboardInput() const {return listenInput;}
        void setListenInput(bool value){listenInput = value;}
        private:

        bool listenInput = true;
    };
}
