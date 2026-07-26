#include "../Novella/Components/Primitives/Sound.hpp"
#include <raylib.h>

namespace Novella{

    Sound::Sound(const std::filesystem::path& path)
        :
        handle(::LoadSound(path.c_str()))
        {};

    const ::Sound& Sound::getHandle() const{

        return handle;
    }

    Sound::~Sound(){

        ::UnloadSound(handle);
    }

}