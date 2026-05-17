#pragma once
#include <string>
#include <nlohmann/json_fwd.hpp>

namespace Novella::Attribute{

    struct Object{
        
        virtual ~Object() = default;
        
        virtual const std::string& getID() const = 0;

        virtual nlohmann::json serialize() const = 0;

        virtual const std::string getType() const = 0;

    };

}