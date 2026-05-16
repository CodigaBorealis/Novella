#pragma once
#include "ResourceManager.hpp"

namespace Novella::Rendering {

    class Renderer{

        public:
        
        Renderer() = delete;
        
        private:

        ResourceManager* resources;
    };
}
