#include "../Novella/Engine.hpp"

namespace Novella{

    Engine::Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps)
        :
        window(width, height , title, fps),
        sceneManager(resourceManager,audioSystem, serializer),
        serializer(resourceManager)
        {}
    void Engine::run(){

        while(window.isOpen()){

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
}