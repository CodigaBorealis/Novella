#pragma once
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace Novella::Components{

    enum class Type : unsigned int;

}

namespace Novella::Attribute{

    struct Object{
        
        virtual ~Object() = default;
        
        virtual unsigned int getID() const = 0;

        virtual nlohmann::json serialize() const = 0;

        virtual Components::Type getType() const = 0;

    };

}