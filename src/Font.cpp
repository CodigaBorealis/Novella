#include "../Novella/Graphics/Font.hpp"
#include <raylib.h>

namespace Novella::Graphics{

    Font::Font(const std::filesystem::path& path)
    :
    handle(::LoadFont(path.c_str()))
    {}

    Font::~Font(){
        
        ::UnloadFont(handle);
    }
        
    int Font::size() const{

        return handle.baseSize;

    }

    const ::Font& Font::getHandle() const{

        return handle;
    }

}