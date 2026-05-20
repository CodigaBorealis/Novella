#include "../Novella/Input/InteractionSystem.hpp"
#include "../Novella/Components/Interactable.hpp"
#include "../Novella/Components/Clickable.hpp"
#include "../Novella/Input/InputSystem.hpp"
#include <iostream>

namespace Novella::Input{
//Can probably optimize this and avoid dynamic cast by actually
//Putting each object into their own container when adding them to the scene and then just traversing it once
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
                        std::cout<< "clicked\n";
                        
                        //dispatcher.trigger(scene, bind.second);
                    }
                }

            }
        }
    }

}