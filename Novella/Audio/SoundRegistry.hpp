#pragma once
#include "AudioResource.hpp"
#include <unordered_map>

namespace Novella::Audio{

    class AudioResource;
    
    class SoundRegistry{
    
        public:

        void registerSound(const AudioResource& resource);

        const AudioResource& get(unsigned int id) const;

        const std::unordered_map<unsigned int, AudioResource>& getAll() const;

        bool contains(unsigned int id) const;

        void clear();
        
        private:

        std::unordered_map<unsigned int, AudioResource> sounds;
    };

}