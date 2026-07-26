#pragma once
#include <filesystem>
#include "../../Primitives/Font.hpp"
namespace Novella{

        struct FontResource{
            
            std::filesystem::path src;
            std::shared_ptr<Font> font;
        };
}