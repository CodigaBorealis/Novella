#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>
#include "../Components/Traits/Object.hpp"

namespace Novella::Traits{

    class Object;

}
//TODO
//The slot datastructure for recycling ids

namespace Novella{

    struct Handle{

        uint32_t index = 0;
        uint32_t generation = 0;
    };

    struct Slot{

        std::unique_ptr<Novella::Traits::Object> object;
        uint32_t generation = 1;
        std::string name;
    };

    class Scene{

        public:

        Scene() = default;
        
        template <std::derived_from<Traits::Object> T, typename... Args>

        Handle createObject(const std::string& name, Args&&... args){

            static_assert(!std::is_abstract_v<T>, "Scene::createObject: Cannot instantiate abstract class");

            auto obj = std::make_unique<T>(std::forward<Args>(args)...);

            return addObject(std::move(obj), name);
            
        }

        template <std::derived_from<Traits::Object> T>

        T* getObject(const Handle& handle){

            Traits::Object* obj = getObjectBase(handle);

            if(!obj) return nullptr;

            if(obj->getTypeID() != T::getStaticTypeID()) return nullptr;

            return static_cast<T*>(obj);
        }

        template <std::derived_from<Traits::Object> T>

        const T* getObject(const Handle& handle) const{

            const Traits::Object* obj = getObjectBase(handle);

            if(!obj) return nullptr;

            if(obj->getTypeID() != T::getStaticTypeID()) return nullptr;

            return static_cast<T*>(obj);
        }

        Handle addObject(std::unique_ptr<Traits::Object> obj, const std::string& name);
        void removeObject(const Handle& id);

        Handle getObjectHandle(const std::string& name) const;

        Traits::Object* getObjectBase(const Handle& handle);

        const Traits::Object* getObjectBase(const Handle& handle) const;

        template<typename Func>

        void forEachObject(Func&& callback){

            for(auto& slot : slots){

                if(slot.object){

                    callback(*slot.object);
                }
            }
        }

        void clearDirtyFlag();
        bool needsSorting() const;

        float getScale() const;

        private:

        bool dirty = false;

        std::vector<Slot> slots;
        std::vector<uint32_t> freeSlots;
        std::unordered_map<std::string, Handle> names;//What the scripting language touches

};
}