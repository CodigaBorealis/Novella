#pragma once

namespace Novella{
    
    class Window;
    class Renderer;
    class ResourceManager;
    class AudioSystem;
    class SceneManager;
    class LayoutSystem;
    class InteractionSystem;
    class Logger;

}

namespace Novella::NScript::Runtime{

    struct Context{

        Window* window;
        Renderer* renderer;
        AudioSystem* audio;
        SceneManager* scene;
        LayoutSystem* layout;
        InteractionSystem* input;
        Logger* logger;
    };

}