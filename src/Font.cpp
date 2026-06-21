#include "../Novella/Components/Primitives/Font.hpp"
#include <raylib.h>

namespace Novella{

    Font::Font(const std::filesystem::path& path)
    :
    handle(::LoadFont(path.string().c_str()))
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