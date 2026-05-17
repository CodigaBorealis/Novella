#pragma once
#include "Audio/AudioSystem.hpp"
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "IO/JsonSerializer.hpp"

namespace Novella{

    class Engine{

        public:

        Engine() = delete;
        
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Engine(Engine&&) noexcept = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);

        void run();

        Rendering::ResourceManager& resources();
        Rendering::Renderer& renderer();
        Audio::AudioSystem& audio();
        SceneManager& scene();
        
        private:

        IO::JsonSerializer serializer;
        SceneManager sceneManager;
        Window window;
        Rendering::Renderer windowRenderer;        
        Rendering::ResourceManager resourceManager;
        Audio::AudioSystem audioSystem;
    };

}