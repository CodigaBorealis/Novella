#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Object.hpp"
#include <cstdint>
#include <memory>
#include <stdexcept>
#include <string>

namespace Novella{

    void Scene::addObject(std::unique_ptr<Traits::Object> obj){

        uint64_t id = ++currentID;

        obj->setHandle(id);

        objectRegistry[id] = obj.get();

        this->drawingOrder.push_back(std::move(obj));

        this->dirty = true;
    
        }
    
    void Scene::removeObject(uint64_t id){

        auto it = objectRegistry.find(id);

        if(it == objectRegistry.end()) throw std::runtime_error("There is no object with this id: '" + std::to_string(id) + "'");

        auto target = it->second;
        
        objectRegistry.erase(id);

        std::erase_if(drawingOrder,[target](const auto& pointer){

            return pointer.get() == target;
        });

        this->dirty = true;

    }

    const std::vector<std::unique_ptr<Traits::Object>>& Scene::objects() const{

        return drawingOrder;
    }

    std::vector<std::unique_ptr<Traits::Object>>& Scene::objects(){

        return drawingOrder;
    }

    Traits::Object* Scene::getObject(uint64_t handle){

            auto it = objectRegistry.find(handle);

            if(it == objectRegistry.end()) return nullptr;
            
            return it->second;
    }

    Traits::Object* Scene::getObject(uint64_t handle) const{

            auto it = objectRegistry.find(handle);

            if(it == objectRegistry.end()) return nullptr;
            
            return it->second;
    }

    uint64_t Scene::getObjectHandle(const std::string& name) const{

        auto it = names.find(name);
        
        if(it == names.end()) return 0;
        
        return it->second;
    }

    void Scene::clearDirtyFlag(){

        this->dirty = false;
    }

    bool Scene::needsSorting() const{

        return this->dirty;
    }
}