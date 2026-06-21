#include "../Novella/Components/Primitives/Texture.hpp"
#include <raylib.h>

namespace Novella{

    Texture::Texture(const std::filesystem::path& path)
    :
    handle(::LoadTexture(path.string().c_str()))
    {}

    Texture::~Texture(){

        ::UnloadTexture(handle);
    }
        
    int Texture::width() const{

        return handle.width;

    }
    
    int Texture::height() const{

        return handle.height;
    }

    const ::Texture2D& Texture::getHandle() const{

        return handle;
    }

}