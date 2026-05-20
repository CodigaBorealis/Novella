#pragma once
#include "../Components/Object.hpp"
#include <concepts>
#include <stdexcept>
#include <type_traits>
#include <memory>
#include <unordered_map>
#include "../Input/Target.hpp"
#include <vector>
#include <optional>
#include <nlohmann/json.hpp>

namespace Novella{

    class Scene{

        public:

        Scene() = default;
        
        template <std::derived_from<Attribute::Object> T, typename... Args>

        T& createObject(Args&&... args){

            static_assert(!std::is_abstract_v<T>, "Scene::createObject: Cannot instantiate abstract class");

            auto obj = std::make_unique<T>(std::forward<Args>(args)...);

            const std::string& id = obj->getID();

            if(id == Novella::Input::Target::SELF) throw std::runtime_error("Scene::CreateObJECT: @SELF is reserved for targeting the component, use other id");

            if(id == Novella::Input::Target::ALL) throw std::runtime_error("Scene::CreateObJECT: @SELF is reserved for targeting everything, use other id");

            if(objectRegistry.contains(id)) throw std::runtime_error("Scene::createObject: id already exists: " + id);

            T& ref = *obj;
            
            objectRegistry.emplace(id, obj.get());

            objs.push_back(std::move(obj));

            this->dirty = true;
            
            return ref;
        }

        //For recovering the specific implementation of the object
        template<typename T>

        T* getObjectAs(const std::string& id){

            auto* base = findObjectByID(id);

            if(!base) throw std::runtime_error("Scene::getObjectAs: id not found: " + id);

            return dynamic_cast<T*>(base);
        }

        void addObject(std::unique_ptr<Attribute::Object> obj);
        void removeObject(const std::string& id);

        Attribute::Object* findObjectByID(const std::string& id);
        Attribute::Object* findObjectByID(const std::string& id) const;

        const std::vector<std::unique_ptr<Attribute::Object>>& objects() const;

        std::vector<std::unique_ptr<Attribute::Object>>& objects();

        
        bool hasBgm() const;
        const std::optional<std::string>& getBgm() const;
        void setBgm(const std::string&);

        void clearDirtyFlag();
        bool needsSorting() const;

        float getScale() const;

        private:

        bool dirty = false;

        std::vector<std::unique_ptr<Attribute::Object>> objs;//For drawing
        std::unordered_map<std::string, Attribute::Object*> objectRegistry;//For lookups
        std::optional<std::string> bgm;//What audio should start playing after creating the scene

};
}