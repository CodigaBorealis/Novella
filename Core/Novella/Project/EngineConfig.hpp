#pragma once
#include <string>
#include <filesystem>
#include <utility>
#include <vector>
#include "../Windowing/Window.hpp"

namespace Novella{

    struct EngineConfig{

        std::filesystem::path root;

        //Window

        unsigned int windowHeight;
        unsigned int windowWidth;
        
        //Internal resolution
        unsigned int width;
        unsigned int height;

        std::string title;
        unsigned int targetFPS = 60;
        std::filesystem::path icon{};
        WindowFlags flags = Novella::WindowFlags::None;

        std::vector<std::pair<std::string, std::string>> sceneData;

    };

}