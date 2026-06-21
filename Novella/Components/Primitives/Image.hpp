#pragma once
#include <raylib.h>
#include <filesystem>

namespace Novella{

    class Image{

        public:
        
        explicit Image(const std::filesystem::path& path);

        Image(const Image&) = delete;
        Image& operator=(const Image&) = delete;

        Image(Image&&) noexcept = default;
        Image& operator=(Image&&) noexcept = default;

        const ::Image& getHandle() const;

        ~Image();
        
        int width() const;
        int height() const;

        private:

        ::Image handle{};
    };
}
