#pragma once
#include <filesystem>
#include <memory>
#include "../../Primitives/Sound.hpp"
#include "../../Primitives/Music.hpp"
#include <variant>

namespace Novella{

    struct AudioResource{
        
        std::filesystem::path src;        
        std::variant<std::unique_ptr<Music>, std::unique_ptr<Sound>> data;
    };

}