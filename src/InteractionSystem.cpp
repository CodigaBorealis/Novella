#include "../Novella/Systems/Input/InteractionSystem.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Clickable.hpp"
#include "../Novella/Components/Traits/Interactable.hpp"
#include "../Novella/Systems/Input/InputSystem.hpp"
#include <cstdint>
#include <queue>
#include <variant>
#include "../Novella/Components/Traits/Object.hpp"
#include "../Novella/Scripting/Interpreter/Interpreter.hpp"

namespace Novella{


//Dynamic casting each frame might cost some performance but its easier to reason about and maintain
//Over separating each object onto their own vector because the gameplay loop isnt really affected
//By the overhead of the cast, since most visual novels don't have 10k objects crammed at once on a scene

    void InteractionSystem::handleKeyboardInput(Scene& scene){

        auto pressed = InputSystem::getKeyboardKeyPressed();

        if(!pressed) return;
        //It shouldnt work likke this but i will leave it for now
        for(const auto& obj : scene.objects()){

            uint64_t handle = obj->getHandle();

            if(const auto* interactable = dynamic_cast<Traits::Interactable*>(obj.get())){

                eventQueue.push(KeyboardEvent{handle, *pressed});

            }
        }
    }

    void InteractionSystem::handleMouseInput(Scene& scene, const Vector2f& mousePosition){

        static int times = 0;

        auto pressed = InputSystem::getMouseButtonPressed();

        if(!pressed) return;

        for(const auto& obj : scene.objects()){

            uint64_t handle = obj->getHandle();

            if(const auto* clickable = dynamic_cast<Traits::Clickable*>(obj.get())){

                if(!clickable->contains(mousePosition)) continue;

                eventQueue.push(MouseEvent{handle,*pressed, mousePosition});

            }
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