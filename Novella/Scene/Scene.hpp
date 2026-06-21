#pragma once
#include <concepts>
#include <cstdint>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>

namespace Novella::Traits{

    class Object;

}

struct Handle{

    uint32_t index;
    uint32_t generation;

    uint64_t to64Bits() const{

        return static_cast<uint64_t>(generation) << 32 | index;
    }

    static Handle from64Bits(uint64_t value){

        return {static_cast<uint32_t>(value & 0xFFFFFFFF), static_cast<uint32_t>(value >> 32)};
    };
};

namespace Novella{

    class Scene{

        public:

        Scene() = default;
        
        template <std::derived_from<Traits::Object> T, typename... Args>

        T& createObject(Args&&... args){

            static_assert(!std::is_abstract_v<T>, "Scene::createObject: Cannot instantiate abstract class");

            auto obj = std::make_unique<T>(std::forward<Args>(args)...);

            T& ref = *obj;
            
            objectRegistry.emplace(++ currentID, obj.get());

            drawingOrder.push_back(std::move(obj));

            this->dirty = true;
            
            return ref;
        }

        void addObject(std::unique_ptr<Traits::Object> obj);
        void removeObject(uint64_t id);

        uint64_t getObjectHandle(const std::string& name) const;

        Traits::Object* getObject(uint64_t handle);
        Traits::Object* getObject(uint64_t handle) const;

        const std::vector<std::unique_ptr<Traits::Object>>& objects() const;

        std::vector<std::unique_ptr<Traits::Object>>& objects();

        void clearDirtyFlag();
        bool needsSorting() const;

        float getScale() const;

        private:

        bool dirty = false;

        uint64_t currentID = 0;

        //I must check on this later
        
        std::vector<std::unique_ptr<Traits::Object>> drawingOrder;
        std::unordered_map<uint64_t, Traits::Object*> objectRegistry;//I could make the registry sequential and just turn a given value into nullptr if the object is deleted
        std::unordered_map<std::string, uint64_t> names;//What the scripting language touches

};
}