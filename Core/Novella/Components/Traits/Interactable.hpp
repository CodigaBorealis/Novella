#pragma once

namespace Novella::Traits{

    struct Interactable{
        
        enum class EventType{

            MouseDown,
            MouseUp,
            MouseMove,
            MouseEnter,
            MouseLeave,
            KeyDown,
            KeyUp,
            FocusGained,
            FocusLost

        };

        struct Event{

            EventType type;

            //std::variant<typename Types> specific types
        };

        virtual ~Interactable() = default;
        
        virtual void handleEvent(const Event& event) = 0;

    };
}
