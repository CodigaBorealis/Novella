#pragma once

namespace Novella::Traits{

    struct Transformable{

        virtual ~Transformable() = default;
        
        void setRotation(float rotation){this->rotation = rotation;};

        float getRotation() const {return rotation;};

        private:

        float rotation = 0;
    };  
}

