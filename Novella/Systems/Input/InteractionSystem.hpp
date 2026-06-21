#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include "InputEvent.hpp"
#include <queue>

namespace Novella::NScript::Runtime{

    class Interpreter;
}

namespace Novella{

    class Scene;

    class InteractionSystem{
        public:

        InteractionSystem() = delete;

        InteractionSystem(NScript::Runtime::Interpreter& interpreter)
            :
            interpreter(interpreter)
            {}

        InteractionSystem(const InteractionSystem&) = delete;

        InteractionSystem& operator=(const InteractionSystem&) = delete;

        InteractionSystem(InteractionSystem&&) = delete;
    
        InteractionSystem& operator=(InteractionSystem&&) = delete;

        void handleKeyboardInput(Scene& scene);
        void handleMouseInput(Scene& scene, const Vector2f& mousePosition);
        void handleInteractions();

        void popEvents();

        void clear();
        
        private:
        
        std::queue<Event> eventQueue;

        NScript::Runtime::Interpreter& interpreter;
    };
}
