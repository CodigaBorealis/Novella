#pragma once
#include <cstdint>
#include <stdexcept>
#include <string>
#include "../Scene/Scene.hpp"
#include "../Attribute/Object.hpp"

namespace Novella::Audio{

    class AudioSystem;
}

namespace Novella::Rendering{

    class Renderer;
        
}

namespace Novella{
        
    class Window;
    
    struct CommandContext{

        CommandContext() = delete;

        CommandContext(Scene* scene, Audio::AudioSystem* audio, Rendering::Renderer* renderer, Window* window)
            :
            scene(scene),
            audio(audio),
            renderer(renderer),
            window(window)
            {}
            
        Scene* scene = nullptr;
        Audio::AudioSystem* audio = nullptr;
        Rendering::Renderer* renderer = nullptr;
        Window* window = nullptr;

        template<typename T>

        T& target(uint64_t targetID) const{

            auto* object = scene->findObjectByID(targetID);

            if(!object) throw std::runtime_error("Target not found: " + std::to_string(targetID));

            auto* casted = dynamic_cast<T*>(object);

            if(!casted) throw std::runtime_error("Invalid target type, id: " + std::to_string(targetID));

            return *casted;
        }
    };

}