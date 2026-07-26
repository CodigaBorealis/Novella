#include "Novella/Primitives/Music.hpp"
#include <raylib.h>

namespace Novella{

    Music::Music(const std::filesystem::path& path)
        :
        handle(::LoadMusicStream(path.c_str()))
        {};

    const ::Music& Music::getHandle() const{

        return handle;
    }

    Music::~Music(){

        ::UnloadMusicStream(handle);
    }

}