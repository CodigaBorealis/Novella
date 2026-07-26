#pragma once
#include <filesystem>
#include <memory>
#include "../../Components/Primitives/Image.hpp"

namespace Novella{

        struct ImageResource{

            std::filesystem::path src;
            std::shared_ptr<Image> image;

        };
}