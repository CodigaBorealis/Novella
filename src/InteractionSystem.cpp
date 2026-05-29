#include "../Novella/Input/InteractionSystem.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Object.hpp"
#include "../Novella/Attribute/Interactable.hpp"
#include "../Novella/Attribute/Clickable.hpp"
#include "../Novella/Input/InputSystem.hpp"
#include <iostream>

namespace Novella::Input{


//Dynamic casting each frame might cost some performance but its easier to reason about and maintain
//Over separating each object onto their own vector because the gameplay loop isnt really affected
//By the overhead of the cast, since most visual novels don't have 10k objects crammed at once on a scene

    void InteractionSystem::handleKeyboardInput(Scene& scene){

        for(const auto& obj : scene.objects()){

            if(const auto* interactable = dynamic_cast<Attribute::Interactable*>(obj.get())){

                for(const auto& bind: interactable->getKeyboardBinds()){

                    if(InputSystem::isKeyPressed(bind.first)){

                        std::cout<< "pressed the key";

                        //dispatcher.trigger(scene, bind.second);
                    }
                }

            }
        }

    }
    void InteractionSystem::handleMouseInput(Scene& scene, const Math::Vector2f& mousePosition){

        static int times = 0;

        for(const auto& obj : scene.objects()){

            if(const auto* clickable = dynamic_cast<Attribute::Clickable*>(obj.get())){

                for(const auto& bind: clickable->getMouseBinds()){

                    if(InputSystem::isMouseButtonPressed(bind.first) && clickable->contains(mousePosition)){

                        times ++;
                        std::cout << times;
                        std::cout << "clicked\n";
                    
                        //dispatcher.trigger(scene, bind.second);
                    }
                }

            }
        }
    }

}