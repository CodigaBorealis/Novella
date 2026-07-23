#pragma once

namespace Novella::Traits{

    struct Clickable{

        virtual ~Clickable() = default;
        
        bool acceptsMouseInput() const{return acceptInput;}
        void setAcceptInput(bool val){acceptInput = val;}
        protected:

        bool acceptInput = true;
    };
}
