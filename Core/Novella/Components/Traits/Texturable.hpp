#pragma once
#include <memory>
#include "../Primitives/Texture.hpp"
namespace Novella::Traits{

    struct Texturable{

        virtual ~Texturable() = default;
        
        void setTexture(std::shared_ptr<Texture> texture){this->texture = texture;};
        
        std::shared_ptr<Texture> getTexture() const{return texture;}

        private:

        std::shared_ptr<Texture> texture;
    };  
}
