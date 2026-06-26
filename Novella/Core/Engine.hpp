#pragma once
#include "../Systems/Audio/AudioSystem.hpp"
#include "Debug/Logger.hpp"
#include "../Systems/Layout/LayoutSystem.hpp"
#include "../Scripting/Interpreter/Interpreter.hpp"
#include "../Windowing/Window.hpp"
#include "../Systems/Renderer/Renderer.hpp"
#include "../Systems/Resources/ResourceManager.hpp"
#include "../Scene/SceneManager.hpp"
#include "../Windowing/WindowFlags.hpp"
#include "../Systems/Input/InteractionSystem.hpp"
#include <memory>

namespace Novella{

    struct EngineConfig;

    class Engine{

        public:
        
        static void create(const std::filesystem::path& projectFile);

        static Engine& instance();

        Engine() = delete;
        
        Engine(const Engine&) = delete;
        Engine& operator=(const Engine&) = delete;

        Engine(Engine&&) noexcept = delete;
        Engine& operator=(Engine&&) noexcept = delete;

        void loadSceneFromFile(const std::filesystem::path& src);
        
        void run();

        ResourceManager& resources();
        Renderer& renderer();
        AudioSystem& audio();
        SceneManager& scene();
        Window& window();
        LayoutSystem& layout();
        //InteractionSystem& input();
        //NScript::Runtime::Interpreter& script();
        Logger& logger();

        private:

        static std::unique_ptr<Engine> singleInstance;
        
        explicit Engine(const EngineConfig& config);

        void computeLayout(Scene* currentScene);
        void handleInput(Scene* currentScene);
        void handleRendering(Scene* currentScene);
        void handleAudio(Scene* currentScene);
        void handleScripting(Scene* currentScene);
        
        std::string lastError = "";

        Window displayWindow;
        Renderer windowRenderer; 

        ResourceManager resourceManager;
        AudioSystem audioSystem;
        SceneManager sceneManager;
        LayoutSystem layoutSystem;
        //NScript::Runtime::Interpreter interpreter;
        //InteractionSystem interactionSystem;
        Logger lg;
    };

}