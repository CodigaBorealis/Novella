#pragma once
#include "Audio/AudioSystem.hpp"
#include "Debug/Logger.hpp"
#include "Layout/LayoutSystem.hpp"
#include "Syntax/NovellaScript/Interpreter/Interpreter.hpp"
#include "Window/Window.hpp"
#include "Rendering/Renderer.hpp"
#include "Rendering/ResourceManager.hpp"
#include "Scene/SceneManager.hpp"
#include "Window/WindowFlags.hpp"
#include "Input/InteractionSystem.hpp"

namespace Novella{

    struct EngineConfig{

        unsigned int width = 1280;
        unsigned int height = 720;

        std::string title = "Novella Engine";
        unsigned int targetFPS = 60;
        std::filesystem::path icon{};
        WindowFlags flags = Novella::WindowFlags::None;

    };

    class Engine{

        public:
        
        Engine();
        
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Engine(Engine&&) noexcept = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        explicit Engine(const EngineConfig& config);

        void loadSceneFromFile(const std::filesystem::path& src);
        
        void run();

        Resources::ResourceManager& resources();
        Rendering::Renderer& renderer();
        Audio::AudioSystem& audio();
        SceneManager& scene();
        Window& window();
        LayoutSystem& layout();
        Input::InteractionSystem& input();
        Syntax::NovellaScript::Interpreter& script();
        Debug::Logger& logger();

        private:

        void computeLayout(Scene* currentScene);
        void handleInput(Scene* currentScene);
        void handleRendering(Scene* currentScene);
        void handleAudio(Scene* currentScene);
        void handleScripting(Scene* currentScene);
        
        std::string lastError = "";

        Window displayWindow;
        Rendering::Renderer windowRenderer; 

        Resources::ResourceManager resourceManager;
        Audio::AudioSystem audioSystem;
        SceneManager sceneManager;
        LayoutSystem layoutSystem;
        Syntax::NovellaScript::Interpreter interpreter;
        Input::InteractionSystem interactionSystem;
        Debug::Logger lg;
    };

}