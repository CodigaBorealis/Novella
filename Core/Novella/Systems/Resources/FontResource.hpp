#pragma once
#include <filesystem>
#include "../../Components/Primitives/Font.hpp"
namespace Novella{

        struct FontResource{
            
            std::filesystem::path src;
            std::shared_ptr<Font> font;
        };
}