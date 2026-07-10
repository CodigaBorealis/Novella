#pragma once
#include <filesystem>

namespace Novella{
    
    class Window;
    class Renderer;
    class ResourceManager;
    class AudioSystem;
    class SceneManager;
    class LayoutSystem;
    class Logger;
}

namespace Novella::NScript::Runtime{

    class Interpreter;

}

namespace Novella::NScript::Runtime{

    struct Context{

        Window* window;
        Renderer* renderer;
        ResourceManager* resources;
        AudioSystem* audio;
        SceneManager* scene;
        LayoutSystem* layout;
        Logger* logger;
        NScript::Runtime::Interpreter* interpreter;
        std::filesystem::path projectRoot;
    };

}