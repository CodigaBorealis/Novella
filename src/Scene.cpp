#include "../Novella/Scene/Scene.hpp"
#include <algorithm>
#include "../Novella/Attribute/Object.hpp"
namespace Novella{

    void Scene::addObject(std::unique_ptr<Attribute::Object> obj){

            const uint64_t id = nextID++;

            obj->setID(id);

            objectRegistry.emplace(id, obj.get());

            objs.push_back(std::move(obj));

            this->dirty = true;
    
        }
    
    void Scene::removeObject(uint64_t id){

        objectRegistry.erase(id);

        std::erase_if(objs, [&](const auto& obj){

            return obj->getID() == id;
        });

        this->dirty = true;

    }

    const std::vector<std::unique_ptr<Attribute::Object>>& Scene::objects() const{

        return objs;
    }

    std::vector<std::unique_ptr<Attribute::Object>>& Scene::objects(){

        return objs;
    }

    Attribute::Object* Scene::findObjectByID(uint64_t targetID){

            auto it = objectRegistry.find(targetID);

            if(it == objectRegistry.end()) return nullptr;
            
            return it->second;
        }

    Attribute::Object* Scene::findObjectByID(uint64_t targetID) const{

        auto it = std::find_if(objs.begin(), objs.end(), [&](const auto& obj){

            return obj->getID() == targetID;
        });

        if(it == objs.end()) return nullptr;
            
        return it->get();
    }

    bool Scene::hasBgm() const{

        return this->bgm != std::nullopt;
    }
        
    const std::optional<std::string>& Scene::getBgm() const{

        return bgm;
    }

    void Scene::setBgm(const std::string& id){

        this->bgm = id;
    }
    
    void Scene::clearDirtyFlag(){

        this->dirty = false;
    }

    bool Scene::needsSorting() const{

        return this->dirty;
    }
}