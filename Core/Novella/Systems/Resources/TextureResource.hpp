#pragma once
#include <filesystem>
#include <memory>
#include "../../Primitives/Texture.hpp"

namespace Novella{


        struct TextureResource{

            std::filesystem::path src;
            std::shared_ptr<Texture> texture;

        };

}