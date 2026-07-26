#include "Novella/Systems/Audio/AudioSystem.hpp"
#include <memory>
#include <raylib.h>
#include <optional>
#include <raylib.h>
#include <string>
#include <variant>
#include "Novella/Systems/Resources/AudioResource.hpp"
#include "Novella/Systems/Resources/ResourceManager.hpp"

namespace Novella{

    AudioSystem::AudioSystem(ResourceManager& resources)
        :
        resources(resources)
        {

            ::InitAudioDevice();           
        }

    AudioSystem::~AudioSystem(){

        ::CloseAudioDevice();

    }

    AudioResource* AudioSystem::getResource(const std::string& name){

        auto it = resources.audio().find(name);

        if(it == resources.audio().end()) return nullptr;

        return &it->second;
    }

    void AudioSystem::play(const std::string& name){

        auto resource = getResource(name);

        if(!resource) return;

        if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource->data)){

            if(!music->get()) return;

            ::PlayMusicStream((*music)->getHandle());
            

        }else if(auto* sound = std::get_if<std::unique_ptr<Sound>>(&resource->data)){

            if(!sound->get()) return; 
            
            ::PlaySound((*sound)->getHandle());
            
        }
    }

    void AudioSystem::stop(const std::string& name){

        auto resource = getResource(name);

        if(!resource) return;

        if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource->data)){
            
            ::StopMusicStream(music->get()->getHandle());

        }else if(auto* sound = std::get_if<std::unique_ptr<Sound>>(&resource->data)){

            ::StopSound(sound->get()->getHandle());
        }
    }

    void AudioSystem::volume(const std::string& name, float volume){
        
        auto resource = getResource(name);

        if(!resource) return;

        if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource->data)){
            
            ::SetMusicVolume(music->get()->getHandle(), volume);

        }else if(auto* sound = std::get_if<std::unique_ptr<Sound>>(&resource->data)){

            ::SetSoundVolume(sound->get()->getHandle(), volume);
        }
    }

    void AudioSystem::pitch(const std::string& name, float pitch){
        
        auto resource = getResource(name);

        if(!resource) return;

        if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource->data)){
            
            ::SetMusicPitch(music->get()->getHandle(), pitch);

        }else if(auto* sound = std::get_if<std::unique_ptr<Sound>>(&resource->data)){

            ::SetSoundPitch(sound->get()->getHandle(), pitch);
        }
    }

    void AudioSystem::pan(const std::string& name, float pan){

       auto resource = getResource(name);

        if(!resource) return;

        if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource->data)){
            
            ::SetMusicPan(music->get()->getHandle(), pan);

        }else if(auto* sound = std::get_if<std::unique_ptr<Sound>>(&resource->data)){

            ::SetSoundPan(sound->get()->getHandle(), pan);
        }    
    }

    void AudioSystem::update(){

        for(auto& [id, resource] : resources.audio()){

            if(auto* music = std::get_if<std::unique_ptr<Music>>(&resource.data)){

                ::UpdateMusicStream(music->get()->getHandle());

            }
        }
    }

    const std::optional<std::string> AudioSystem::getCurrentBGM() const{

        return this->currentBGM;
    }

    float AudioSystem::getMasterVolume() const{

        return ::GetMasterVolume();
    }
}