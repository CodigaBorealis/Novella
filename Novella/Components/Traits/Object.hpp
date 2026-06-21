#pragma once
#include <cstdint>
namespace Novella::Traits{

    struct TypeRegistry{

        static uint32_t nextID(){

            static uint32_t id = 0;

            return id ++;
        }
    };

    struct Object{
        
        Object() = default;

        virtual ~Object() = default;

        virtual uint32_t getTypeID() const = 0;
        
        uint64_t getHandle() const{

            return handle;
        }

        void setHandle(uint64_t id){

            this->handle = id;
        }

        private:

        uint64_t handle = 0;
    };

    template <typename Derived>

        struct RegisteredObject : public Object{

            uint32_t getTypeID() const override{

            return getStaticTypeID();
        }


        static uint32_t getStaticTypeID(){

            static const uint32_t id = TypeRegistry::nextID();

            return id;
        }
    };

}