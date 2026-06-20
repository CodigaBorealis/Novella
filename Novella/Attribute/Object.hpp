#pragma once
#include <string>
#include <cstdint>
namespace Novella::Attribute{

    struct Object{
        
        Object() = delete;

        explicit Object(const std::string& type)
            :
            type(type)
            {}

        virtual ~Object() = default;

        virtual const std::string& getType() const = 0;
        
        const uint64_t getHandle(){

            return handle;
        }

        void setHandle(uint64_t id){

            this->handle = id;
        }

        uint64_t handle = 0;

        std::string type;
    };

}