#pragma once

#pragma once
#include <raylib.h>
#include <filesystem>

namespace Novella{

    class Music{

        public:
        
        explicit Music(const std::filesystem::path& path);

        Music(const Music&) = delete;
        Music& operator=(const Music&) = delete;

        Music(Music&&) noexcept = delete;
        Music& operator=(Music&&) noexcept = delete;

        const ::Music& getHandle() const;

        ~Music();

        private:

        ::Music handle{};
    };
}
