#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Clickable.hpp"
#include "../Novella/Components/Traits/Interactable.hpp"
#include "../Novella/Systems/Input/InputSystem.hpp"
#include <queue>
#include <variant>
#include "../Novella/Components/Traits/Object.hpp"
#include "../Novella/Scripting/Interpreter/Interpreter.hpp"
#include <iostream>

namespace Novella{  

    void InteractionSystem::rebuildCaches(Scene& scene){

        InteractableCache.clear();
        clickableCache.clear();

        scene.forEachObject([this](Traits::Object& object){

            if(auto* interactable = dynamic_cast<Traits::Interactable*>(&object)){

                InteractableCache.push_back({object.objectHandle(), interactable});
            }

            if(auto* clickable = dynamic_cast<Traits::Clickable*>(&object)){

                clickableCache.push_back({object.objectHandle(), clickable});
            }
        });

    }

    void InteractionSystem::handleKeyboardInput(Scene& scene){

        auto pressed = InputSystem::getKeyboardKeyPressed();

        if(!pressed) return;

        std::cout << "key pressed: " << static_cast<int>(pressed.value()) << "\n";

        if(scene.needsSorting()){

            rebuildCaches(scene);
        }
        
        for(const auto& interactable : InteractableCache){

            eventQueue.push(KeyboardEvent{interactable.handle, *pressed});
        }

        };
    
    void InteractionSystem::handleMouseInput(Scene& scene, const Vector2f& mousePosition){

        static int delay = 0;

        delay ++;
        
        if(delay == 50){

            std::cout << "MOUSE X: " << mousePosition.x << " MOUSE Y: " << mousePosition.y << "\n";

            delay = 0;
        }   

        auto pressed = InputSystem::getMouseButtonPressed();

        if(!pressed) return;

        for(const auto& clickable : clickableCache){

            eventQueue.push(MouseEvent{clickable.handle, *pressed, mousePosition});
        }
    }

    void InteractionSystem::handleInteractions(){

        while(!eventQueue.empty()){

            auto event = std::move(eventQueue.front());

            this->interpreter.interpretEvent(event);

            eventQueue.pop();
        }

    }

    void InteractionSystem::clear(){

        std::queue<Event> cleanQueue;

        eventQueue.swap(cleanQueue);
    }
}