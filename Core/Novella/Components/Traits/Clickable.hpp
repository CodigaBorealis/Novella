#pragma once
#include "../../Core/Math/Vector2x.hpp"

namespace Novella::Traits{

    struct Clickable{

        virtual ~Clickable() = default;
        
        bool acceptsMouseInput() const{return acceptInput;}
        void setAcceptInput(bool val){acceptInput = val;}
        private:

        bool acceptInput = true;
    };
}
