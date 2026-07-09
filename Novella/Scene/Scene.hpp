#pragma once
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>
#include "../Components/Traits/Object.hpp"
#include "Handle.hpp"
#include "Slot.hpp"
namespace Novella::Traits{

    class Object;

}

namespace Novella{

    class Scene{

        public:

        Scene() = default;
        
        template <typename Interface>
        requires std::is_class_v<Interface>

        Interface* getInterface(const Handle& handle){

            Traits::Object* object = getObjectBase(handle);

            if(!object) return nullptr;

            return dynamic_cast<Interface*>(object);
        }

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

        const Handle getObjectHandle(const std::string& name) const;

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
        
        size_t objectCount() const;
        
        void markDirty();
        
        void clearDirtyFlag();
        bool needsSorting() const;

        float getScale() const;

        std::optional<std::string> findName(Handle targetHandle) const;

        private:

        bool dirty = false;

        std::vector<Slot> slots;
        std::vector<uint32_t> freeSlots;
        std::unordered_map<std::string, Handle> names;//What the scripting language touches

};
}