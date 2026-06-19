#pragma once
#include "ClickEvent.hpp"
#include "../Math/Vector2x.hpp"
#include "KeyEvent.hpp"
#include <variant>
#include <queue>
#include <nlohmann/json_fwd.hpp>

namespace Novella{

    class Scene;

    class CommandContext;

}

namespace Novella::Syntax::NovellaScript{

    class Interpreter;
}

namespace Novella::Input{

    class InteractionSystem{

        struct ScriptCallback{

            std::string moduleName;
            std::string functionName;

            std::vector<nlohmann::json> args;
        };

        public:

        InteractionSystem() = delete;

        InteractionSystem(Syntax::NovellaScript::Interpreter& interpreter)
            :
            interpreter(interpreter)
            {}

        InteractionSystem(const InteractionSystem&) = delete;

        InteractionSystem& operator=(const InteractionSystem&) = delete;

        InteractionSystem(InteractionSystem&&) = delete;
    
        InteractionSystem& operator=(InteractionSystem&&) = delete;

        void handleKeyboardInput(Scene& scene);
        void handleMouseInput(Scene& scene, const Math::Vector2f& mousePosition);
        void handleInteractions();

        void popEvents();

        void clear();
        
        private:
        
        using Event = std::variant<KeyEvent, ClickEvent>;

        std::queue<Event> eventQueue;

        Syntax::NovellaScript::Interpreter& interpreter;
    };

}