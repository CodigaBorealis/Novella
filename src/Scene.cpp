#include "../Novella/Scene/Scene.hpp"
#include <algorithm>

namespace Novella{

    void Scene::addObject(std::unique_ptr<Attribute::Object> obj){

            const std::string& id = obj->getID();

            if(objectRegistry.contains(id)) throw std::runtime_error("Scene::addObject: An object with this id already exists in the scene " + id);

            objectRegistry[id] = obj.get();

            objs.push_back(std::move(obj));
    
        }
    
    void Scene::removeObject(const std::string& id){

        objectRegistry.erase(id);

        std::erase_if(objs, [&](const auto& obj){

            return obj->getID() == id;
        });
    }

    const std::vector<std::unique_ptr<Attribute::Object>>& Scene::objects() const{

        return objs;
    }

    Attribute::Object* Scene::findObjectByID(const std::string& id){

            auto it = objectRegistry.find(id);

            if(it == objectRegistry.end()) return nullptr;
            
            return it->second;
        }

    Attribute::Object* Scene::findObjectByID(const std::string& id) const{

        auto it = std::find_if(objs.begin(), objs.end(), [&](const auto& obj){

            return obj->getID() == id;
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
        
}