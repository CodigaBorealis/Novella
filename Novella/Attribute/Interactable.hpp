#pragma once
#include <nlohmann/json.hpp>

namespace Novella::Attribute{

    struct Interactable{
        
        public:

        virtual ~Interactable() = default;
        
        virtual bool acceptsKeyboardInput() = 0;
    };
}
