#pragma once
#include <filesystem>
#include <memory>
#include "../../Components/Primitives/Texture.hpp"

namespace Novella{


        struct TextureResource{

            std::filesystem::path src;
            std::shared_ptr<Texture> texture;

        };

}