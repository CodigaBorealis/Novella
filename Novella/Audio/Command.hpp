#pragma once

namespace Novella::Audio {

    struct Command{
        
        enum Type{

        Play,
        Stop,
        SetVolume,
        SetPan,
        SetPitch
            
        };  
        
        Type type;
        unsigned int id;
        float value = 1.0f;

        constexpr Command(Type t, unsigned int  i, float v) noexcept: type(t), id(i), value(v) {}
        };

}
