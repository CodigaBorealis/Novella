#pragma once
#include <raylib.h>
#include <filesystem>

namespace Novella{

    class Texture{

        public:
        
        explicit Texture(const std::filesystem::path& path);

        Texture(const Texture&) = delete;
        Texture& operator=(const Texture&) = delete;

        Texture(Texture&&) noexcept = default;
        Texture& operator=(Texture&&) noexcept = default;

        const ::Texture2D& getHandle() const;

        ~Texture();
        
        int width() const;
        int height() const;

        private:

        ::Texture2D handle{};
    };
}
