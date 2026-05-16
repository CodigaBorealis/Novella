#pragma once
#include <string>

namespace Novella::Core {

    struct Object{
        
        virtual ~Object() = default;

        virtual void update(){}
        virtual void render(){}

        virtual void getType() = 0;
        virtual void serialize() = 0;
        
        virtual std::string getID() const = 0;

        int renderLayer() const;
    };

}