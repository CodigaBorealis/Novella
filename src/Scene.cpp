#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Object.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

namespace Novella{

    void Scene::addObject(std::unique_ptr<Attribute::Object> obj){

        uint64_t id = ++currentID;

        obj->setHandle(id);

        objectRegistry[id] = obj.get();

        objs.push_back(std::move(obj));

        this->dirty = true;
    
        }
    
    void Scene::removeObject(uint64_t id){

        auto it = objectRegistry.find(id);

        if(it == objectRegistry.end()) throw std::runtime_error("There is no object with this id: '" + std::to_string(id) + "'");

        auto target = it->second;
        
        objectRegistry.erase(id);

        std::erase_if(objs,[target](const auto& pointer){

            return pointer.get() == target;
        });

        this->dirty = true;

    }

    const std::vector<std::unique_ptr<Attribute::Object>>& Scene::objects() const{

        return objs;
    }

    std::vector<std::unique_ptr<Attribute::Object>>& Scene::objects(){

        return objs;
    }

    Attribute::Object* Scene::findObjectByID(const std::string& id){

            auto it = names.find(id);

            if(it == names.end()) throw std::runtime_error("There is no object with this id '" + id + "'");
            
            return objectRegistry.at(it->second);
        }

    Attribute::Object* Scene::findObjectByID(const std::string& id) const{

           auto it = names.find(id);

            if(it == names.end()) throw std::runtime_error("There is no object with this id '" + id + "'");
            
            return objectRegistry.at(it->second);
    }
    
    void Scene::clearDirtyFlag(){

        this->dirty = false;
    }

    bool Scene::needsSorting() const{

        return this->dirty;
    }
}