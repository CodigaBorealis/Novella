#pragma once
#include <concepts>
#include <cstdint>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>

namespace Novella::Attribute{

    class Object;

}

namespace Novella{

    class Scene{

        public:

        Scene() = default;
        
        template <std::derived_from<Attribute::Object> T, typename... Args>

        T& createObject(Args&&... args){

            static_assert(!std::is_abstract_v<T>, "Scene::createObject: Cannot instantiate abstract class");

            auto obj = std::make_unique<T>(std::forward<Args>(args)...);

            T& ref = *obj;
            
            objectRegistry.emplace(++ currentID, obj.get());

            objs.push_back(std::move(obj));

            this->dirty = true;
            
            return ref;
        }

        //For recovering the specific implementation of the object
        template<typename T>

        T* getObjectAs(const std::string& id){

            auto* base = findObjectByID(id);

            if(!base) throw std::runtime_error("Scene::getObjectAs: id not found: "  + id);

            return dynamic_cast<T*>(base);
        }

        void addObject(std::unique_ptr<Attribute::Object> obj);
        void removeObject(uint64_t id);

        Attribute::Object* findObjectByID(const std::string& id);
        Attribute::Object* findObjectByID(const std::string& id) const;

        const std::vector<std::unique_ptr<Attribute::Object>>& objects() const;

        std::vector<std::unique_ptr<Attribute::Object>>& objects();
        
        const std::optional<std::string>& getBgm() const;
        void setBgm(const std::string&);

        void clearDirtyFlag();
        bool needsSorting() const;

        float getScale() const;

        private:

        bool dirty = false;

        uint64_t currentID = 0;

        std::vector<std::unique_ptr<Attribute::Object>> objs;//For drawing
        std::unordered_map<uint64_t, Attribute::Object*> objectRegistry;//This could be a vector but i dont want to deal with invalid indexes right now
        std::unordered_map<std::string, uint64_t> names;//What the scripting language touches

};
}