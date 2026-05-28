#pragma once
#include <nlohmann/json_fwd.hpp>
#include <cstdint>

namespace Novella::Components{

    enum class Type : unsigned int;

}

namespace Novella::Attribute{

    struct Object{
        
        virtual ~Object() = default;
        
        virtual uint64_t  getID() const = 0;
        
        virtual void setID(uint64_t) = 0;

        virtual nlohmann::json serialize() const = 0;

        virtual Components::Type getType() const = 0;

    };

}