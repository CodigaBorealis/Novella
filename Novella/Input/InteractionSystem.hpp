#pragma once
#include "ClickEvent.hpp"
#include "CommandDispatcher.hpp"
#include "../Math/Vector2x.hpp"
#include "KeyEvent.hpp"
#include <variant>
#include <queue>

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
        void handleInteractions(CommandContext& context);

        void addClickBinding(uint64_t objectID, Mouse::Button button, Alias commandAlias, const nlohmann::json& args);
        void addKeyBinding(uint64_t objectID, Keyboard::Key key, Alias commandAlias, const nlohmann::json& args);
        
        private:
        
        using Event = std::variant<KeyEvent, ClickEvent>;

        CommandDispatcher dispatcher;
        std::queue<Event> eventQueue;

    };

}