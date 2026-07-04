#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Components/Traits/Object.hpp"
#include <memory>
#include <stdexcept>
#include <string>

namespace Novella{

    Handle Scene::addObject(std::unique_ptr<Traits::Object> obj, const std::string& name){
        
        if(name.empty()) throw std::runtime_error("Name cannot be empty");

        if(names.contains(name)) throw std::runtime_error("An object with this name already exists: " + name);

        uint32_t index;

        if(freeSlots.empty()){

            index = slots.size();
            slots.push_back({std::move(obj), 0, name});

        }else{

            index = freeSlots.back();
            freeSlots.pop_back();

            slots[index].object = std::move(obj);
            slots[index].name = name;
        }

        this->dirty = true;

        Handle handle{index, slots[index].generation};

        names.emplace(name, handle);

        return handle;

    }
    
    void Scene::removeObject(const Handle& handle){

        if(handle.index >= slots.size()) return;

        Slot& slot = slots[handle.index];

        if(slot.generation != handle.generation) return;

        slot.object.reset();
        slot.generation ++;

        names.erase(slot.name);

        slot.name.clear();

        freeSlots.push_back(handle.index);

        this->dirty = true;

    }

    Traits::Object* Scene::getObjectBase(const Handle& handle){

        if(handle.index >= slots.size()) return nullptr;

        Slot& slot = slots[handle.index];

        if(slot.generation != handle.generation) return nullptr;

        return slot.object.get();
        
    }

    const Traits::Object* Scene::getObjectBase(const Handle& handle) const{

        if(handle.index >= slots.size()) return nullptr;

        const Slot& slot = slots[handle.index];

        if(slot.generation != handle.generation) return nullptr;

        return slot.object.get();
        
    }

    const Handle& Scene::getObjectHandle(const std::string& name) const{

        auto it = names.find(name);
        
        if(it == names.end()) throw std::runtime_error("Object not found: " + name);
        
        const Handle& handle = it->second;

        if(handle.index >= slots.size() || slots[handle.index].generation != handle.generation) throw std::runtime_error("Stale handle in name map: " + name);
        return it->second;
    }

    void Scene::clearDirtyFlag(){

        this->dirty = false;
    }

    bool Scene::needsSorting() const{

        return this->dirty;
    }
}