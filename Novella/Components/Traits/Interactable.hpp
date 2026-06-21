#pragma once

namespace Novella::Traits{

    struct Interactable{
        
        virtual ~Interactable() = default;
        
        virtual bool acceptsKeyboardInput() = 0;
    };
}
