#include "../Novella/Components/Primitives/Image.hpp"
#include <raylib.h>

namespace Novella{

    Image::Image(const std::filesystem::path& path)
    :
    handle(::LoadImage(path.string().c_str()))
    {}

    Image::~Image(){

        ::UnloadImage(handle);
    }
        
    int Image::width() const{

        return handle.width;

    }
    
    int Image::height() const{

        return handle.height;
    }

    const ::Image& Image::getHandle() const{

        return handle;
    }
}