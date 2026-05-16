#include "../Novella/Audio/SoundRegistry.hpp"

namespace Novella::Audio{

    void SoundRegistry::registerSound(const AudioResource& asset){

        sounds.emplace(asset.id, asset);
    }

    const AudioResource& SoundRegistry::get(unsigned int id) const{

        return sounds.at(id);
    }

    bool SoundRegistry::contains(unsigned int id) const{

        return sounds.contains(id);
    }
    
    const std::unordered_map<unsigned int, AudioResource>& SoundRegistry::getAll() const{

        return sounds;
    }

    void SoundRegistry::clear(){

        this->sounds.clear();
    }
}
 