#include "../Novella/Systems/Audio/AudioBackend.hpp"
#include <optional>
#include <raylib.h>
#include <stdexcept>
#include <string>
namespace Novella::Audio{

    AudioBackend::AudioBackend(ResourceManager& resources)
        :
        resources(resources.audio())
        {

            ::InitAudioDevice();           
        }

    AudioBackend::~AudioBackend(){

        clear();
        ::CloseAudioDevice();

    }

    const ResourceManager::AudioResource& AudioBackend::getResource(const std::string& name){

        auto it = resources.find(name);

        if(it == resources.end()) throw std::runtime_error("audio resource not found '" + name + "'");

        return it->second;

    }

    ::Music& AudioBackend::getMusicStream(const std::string& name){

        auto it = musicStreams.find(name);

        if(it == musicStreams.end()) throw std::runtime_error("resource has not been loaded as music '" + name + "'");
        
        return it->second;
    }

    ::Sound& AudioBackend::getSoundStream(const std::string& name){

       auto it = soundStreams.find(name);

        if(it == soundStreams.end()) throw std::runtime_error("resource has not been loaded as sfx '" + name + "'");
        
        return it->second;
    }

    void AudioBackend::play(const std::string& name){

        auto& resource = getResource(name);

        if(resource.type == "music"){
            
            auto& music = getMusicStream(name);

            ::PlayMusicStream(music);
            
            music.looping = true;
            
            currentBGM = name;

        }else if(resource.type == "sfx"){

            ::PlaySound(getSoundStream(name));

        }else{
            
            throw std::runtime_error("There is no resource registered under this name '" + name + "'");
        }
    }

    void AudioBackend::stop(const std::string& name){

        auto& resource = getResource(name);

        if(resource.type == "music"){

            ::StopMusicStream(getMusicStream(name));

            currentBGM = std::nullopt;

        }else if(resource.type == "sfx"){

            ::StopSound(getSoundStream(name));
        }
    }

    void AudioBackend::volume(const std::string& name, float volume){
        
        auto& resource = getResource(name);

        if(resource.type == "music"){


            ::SetMusicVolume(getMusicStream(name), volume);

        }else{


            ::SetSoundVolume(getSoundStream(name), volume);
        }
    }

    void AudioBackend::pitch(const std::string& name, float volume){

        auto& resource = getResource(name);

        if(resource.type == "music"){

            ::SetMusicPitch(getMusicStream(name), volume);

        }else{

            ::SetSoundPitch(getSoundStream(name), volume);
        }        
    }

    void AudioBackend::pan(const std::string& name, float volume){

        auto& resource = getResource(name);

        if(resource.type == "music"){


            ::SetMusicPan(getMusicStream(name), volume);

        }else{


            ::SetSoundPan(getSoundStream(name), volume);
        }        
    }

    void AudioBackend::update(){

        for(auto& [id, music] : musicStreams){

            ::UpdateMusicStream(music);

        }

    }

    void AudioBackend::clear(){

        for(auto& [id, sound] : soundStreams){

            ::StopSound(sound);
            ::UnloadSound(sound);
        }

        for(auto& [id, music] : musicStreams){

            ::StopMusicStream(music);
            ::UnloadMusicStream(music);
        }

        this->musicStreams.clear();
        this->soundStreams.clear();
    }

    const std::optional<std::string> AudioBackend::getCurrentBGM() const{

        return this->currentBGM;
    }

    void AudioBackend::reloadResources(){
        
        auto bgm = currentBGM;
        
        clear();

        loadResources();

        if(bgm && musicStreams.contains(bgm.value())){

            play(bgm.value());
        }
    }

    void AudioBackend::loadResources(){
        
        for(const auto& resource : resources){

            if(resource.second.type == "music"){

                musicStreams.emplace(resource.first, ::LoadMusicStream(resource.second.src.string().c_str()));

            }else if(resource.second.type == "sfx"){

                soundStreams.emplace(resource.first, ::LoadSound(resource.second.src.string().c_str()));

            }else{

                throw std::runtime_error("Invalid type for audio resource '" + resource.second.type + "'");
            }
         
        }
    }

    bool AudioBackend::isRegistered(const std::string& name){

        return musicStreams.contains(name) || musicStreams.contains(name);
    }

    float AudioBackend::getMasterVolume() const{

        return ::GetMasterVolume();
    }
}