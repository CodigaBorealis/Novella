#pragma once
#include <nlohmann/json_fwd.hpp>
#include <string>

namespace Novella::Attribute{

    struct Object{
        
        Object() = delete;

        explicit Object(const std::string& id, const std::string& type)
            :
            id(id),
            type(type)
            {}

        virtual ~Object() = default;
        
        virtual const std::string&  getID() const = 0;
        
        virtual void setID(const std::string& id) = 0;

        virtual nlohmann::json serialize() const = 0;

        virtual const std::string& getType() const = 0;
        
        std::string type;
        std::string id;
    };

}