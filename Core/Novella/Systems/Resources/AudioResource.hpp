#pragma once
#include <filesystem>
#include <memory>
#include "../../Components/Primitives/Sound.hpp"
#include "../../Components/Primitives/Music.hpp"
#include <variant>

namespace Novella{

    struct AudioResource{
        
        std::filesystem::path src;        
        std::variant<std::unique_ptr<Music>, std::unique_ptr<Sound>> data;
    };

}