#pragma once
#include "../../Core/Math/Vector2x.hpp"
#include "InputEvent.hpp"
#include <queue>
#include <vector>

namespace Novella::Traits{

    struct Interactable;
    struct Clickable;
}

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

        void rebuildCaches(Scene& scene);

        void popEvents();

        void clear();
        
        private:
        
        struct ClickableCacheEntry{

            uint64_t handle;
            Traits::Clickable* trait;
        };

        struct InteractableCacheEntry{

            uint64_t handle;
            Traits::Interactable* trait;
        };

        std::queue<Event> eventQueue;

        std::vector<InteractableCacheEntry> InteractableCache;
        std::vector<ClickableCacheEntry> clickableCache;

        NScript::Runtime::Interpreter& interpreter;
    };
}
