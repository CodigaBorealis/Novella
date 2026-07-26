#pragma once

#pragma once
#include <raylib.h>
#include <filesystem>

namespace Novella{

    class Sound{

        public:
        
        explicit Sound(const std::filesystem::path& path);

        Sound(const Sound&) = delete;
        Sound& operator=(const Sound&) = delete;

        Sound(Sound&&) noexcept = delete;
        Sound& operator=(Sound&&) noexcept = delete;

        const ::Sound& getHandle() const;

        ~Sound();
    
        private:

        ::Sound handle{};
    };
}
