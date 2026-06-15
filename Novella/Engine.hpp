#pragma once
#include "Audio/AudioSystem.hpp"
#include "Layout/LayoutSystem.hpp"
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "Window/WindowFlags.hpp"
#include "Input/InteractionSystem.hpp"

namespace Novella{

    class Engine{

        public:
        
        Engine() = delete;
        
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Engine(Engine&&) noexcept = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps);

        Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, WindowFlags flags);

        Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon);

        Engine(unsigned int width, unsigned int height, const std::string& title, unsigned int fps, const std::filesystem::path& icon, WindowFlags flags);

        void loadSceneFromFile(const std::filesystem::path& src);
        
        void run();

        Resources::ResourceManager& resources();
        Rendering::Renderer& renderer();
        Audio::AudioSystem& audio();
        SceneManager& scene();
        Window& window();
        LayoutSystem& layout();
        Input::InteractionSystem& input();

        private:

        void computeLayout(Scene* currentScene);
        void handleInput(Scene* currentScene);
        void handleRendering(Scene* currentScene);
        void handleAudio(Scene* currentScene);
        
        std::string lastError = "";

        Window displayWindow;
        Rendering::Renderer windowRenderer; 

        Resources::ResourceManager resourceManager;
        Audio::AudioSystem audioSystem;
        SceneManager sceneManager;
        LayoutSystem layoutSystem;
        Input::InteractionSystem interactionSystem;
    };

}