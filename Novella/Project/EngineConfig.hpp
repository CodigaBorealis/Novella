#pragma once
#include <string>
#include <filesystem>
#include "../Windowing/WindowFlags.hpp"

namespace Novella{

    struct EngineConfig{

        unsigned int width;
        unsigned int height;

        std::string title;
        unsigned int targetFPS = 60;
        std::filesystem::path icon{};
        WindowFlags flags = Novella::WindowFlags::None;

    };

}