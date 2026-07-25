#pragma once
#include <cstdint>
#include "Object.hpp"
#include <unordered_map>
#include <string>

namespace Novella::Traits{

    struct Primitive{

        struct PropertyDescriptor{

            uint32_t typeID;
            void* (*getPointer)(Object&);
                
            bool readOnly = false;
        };

        virtual const std::unordered_map<std::string, PropertyDescriptor>& properties() const = 0;

    };

}