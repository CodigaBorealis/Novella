#pragma once
#include <filesystem>

namespace Novella{
    
    class Window;
    class Renderer;
    class ResourceManager;
    class AudioSystem;
    class SceneManager;
    class LayoutSystem;
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
        NScript::Runtime::Interpreter* interpreter;
        std::filesystem::path projectRoot;
    };

}