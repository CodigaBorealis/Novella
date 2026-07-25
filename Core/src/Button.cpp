#include "../Novella/Components/UI/Button.hpp"
#include <stdexcept>
#include <string>
#include "../Novella/Components/UI/Sprite.hpp"

namespace Novella::UI{

    void Button::validate() const{

        if(!childAs<Sprite>("background")) throw std::runtime_error("Button requires a Sprite component with the role 'background'");
        
    }
}