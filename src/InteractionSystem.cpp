#include "../Novella/Input/InteractionSystem.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Clickable.hpp"
#include "../Novella/Attribute/Interactable.hpp"
#include "../Novella/Input/InputSystem.hpp"
#include "../Novella/Input/ClickEvent.hpp"
#include <variant>
#include <iostream>
namespace Novella::Input{


//Dynamic casting each frame might cost some performance but its easier to reason about and maintain
//Over separating each object onto their own vector because the gameplay loop isnt really affected
//By the overhead of the cast, since most visual novels don't have 10k objects crammed at once on a scene

    void InteractionSystem::handleKeyboardInput(Scene& scene){

        auto pressed = InputSystem::getKeyboardKeyPressed();

        if(!pressed) return;
        //It shouldnt work likke this but i will leave it for now
        for(const auto& obj : scene.objects()){

            if(const auto* Interactable = dynamic_cast<Attribute::Interactable*>(obj.get())){

                eventQueue.push(Novella::Input::KeyEvent{obj->getID(), *pressed});

            }
        }
    }

    void InteractionSystem::handleMouseInput(Scene& scene, const Math::Vector2f& mousePosition){

        static int times = 0;

        auto pressed = InputSystem::getMouseButtonPressed();

        if(!pressed) return;

        for(const auto& obj : scene.objects()){

            if(const auto* clickable = dynamic_cast<Attribute::Clickable*>(obj.get())){

                if(!clickable->contains(mousePosition)) continue;

                eventQueue.push(Novella::Input::ClickEvent{obj->getID(), *pressed, mousePosition});

            }
        }
    }

    void InteractionSystem::handleInteractions(CommandContext& context){

        while(!eventQueue.empty()){

            auto event = std::move(eventQueue.front());

            eventQueue.pop();

            std::visit([&](auto&& e){

                dispatcher.dispatch(e, context);

            }, event);
        }

    }

    void InteractionSystem::addClickBinding(uint64_t objectID, Mouse::Button button, Alias commandAlias, const nlohmann::json& args){

        dispatcher.addClickBinding(objectID, button, commandAlias, args);

    };

    void InteractionSystem::addKeyBinding(uint64_t objectID, Keyboard::Key key, Alias commandAlias, const nlohmann::json& args){

        dispatcher.addKeyBinding(objectID, key, commandAlias, args);
    };
}