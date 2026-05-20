#pragma once
#include "CommandDispatcher.hpp"
#include "../Math/Vector2x.hpp"
namespace Novella::Input{

    class InteractionSystem{

        public:

        InteractionSystem() = default;

        InteractionSystem(const InteractionSystem&) = delete;

        InteractionSystem& operator=(const InteractionSystem&) = delete;

        InteractionSystem(InteractionSystem&&) = delete;
    
        InteractionSystem& operator=(InteractionSystem&&) = delete;

        void handleKeyboardInput(Scene& scene);
        void handleMouseInput(Scene& scene, const Math::Vector2f& mousePosition);

        private:
        
        CommandDispatcher dispatcher;
    };

}