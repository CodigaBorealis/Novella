#pragma once
#include "Interactable.hpp"

namespace Novella::Traits{

    struct EventReceiver{

        virtual ~EventReceiver() = default;
        
        virtual bool handleEvent(const Interactable::Event& event) = 0;
    };

}