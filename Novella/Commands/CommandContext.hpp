#pragma once

    namespace Audio{

        class AudioSystem;
    }

    namespace Rendering{

        class Renderer;
        
    }

    class Scene;
        
    class Window;

    namespace Attribute{
        
        class Object;

    }

namespace Novella{

    struct CommandContext{

        public:
        Scene* scene = nullptr;
        Attribute::Object* target = nullptr;
        Audio::AudioSystem* audio = nullptr;
        Rendering::Renderer* renderer = nullptr;
        Window* window = nullptr;
        
    };

}