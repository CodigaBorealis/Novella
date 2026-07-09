#pragma once
#include <raylib.h>
#include <filesystem>

namespace Novella{

    class Font{
    
    public:

        Font() = delete;

        explicit Font(const std::filesystem::path& path);

        Font(const Font&) = delete;
        Font& operator=(const Font&) = delete;

        Font(Font&&) noexcept = delete;
        Font& operator=(Font&&) noexcept = delete;

        const ::Font& getHandle() const;

        ~Font();

        int size() const;

    private:

        ::Font handle{};

    };
}
