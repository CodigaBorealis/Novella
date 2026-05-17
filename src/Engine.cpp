#include "../Novella/Engine.hpp"

namespace Novella{

    Engine::~Engine(){

        resourceManager.clear();
        sceneManager.clear();
        audioSystem.clear();
        displayWindow.close();
    }

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
        :
        displayWindow(width, height , title, fps),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, flags),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon)
        :
        displayWindow(width, height , title, fps, icon),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager)
        {}

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon, WindowFlags flags)
        :
        displayWindow(width, height , title, fps, icon, flags),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager)
        {}

    void Engine::run(){
        
        while(displayWindow.isOpen()){

            audioSystem.update();

            windowRenderer.beginFrame();
            
            renderer().drawScene(sceneManager.getCurrentScene());

            windowRenderer.endFrame();

        }
    }

    Rendering::ResourceManager& Engine::resources(){

        return resourceManager;
    }

    Rendering::Renderer& Engine::renderer(){

        return windowRenderer;
    }

    Audio::AudioSystem& Engine::audio(){

        return audioSystem;
    }

    SceneManager& Engine::scene(){

        return sceneManager;
    }

    Window& Engine::window(){

        return displayWindow;
    }
}