#include "../Novella/Audio/AudioSystem.hpp"
#include <optional>
namespace Novella::Audio{
    
    AudioSystem::AudioSystem(Resources::ResourceManager& resources)
        :
        backend(resources)
        {}


    AudioSystem::~AudioSystem(){

        backend.clear();
    }

    void AudioSystem::play(const std::string& name){

        backend.play(name);
    }

    void AudioSystem::stop(const std::string& name){

        backend.stop(name);
    }

    void AudioSystem::volume(const std::string& name, float volume){

        backend.volume(name, volume);
    }

    void AudioSystem::pitch(const std::string& name, float pitch){

        backend.pitch(name, pitch);
    }

    void AudioSystem::pan(const std::string& resourceName, float pan){

        backend.pan(resourceName, pan);
    }

    void AudioSystem::update(){

        backend.update();
    }

    const std::optional<std::string> AudioSystem::getCurrentBGM() const{

        return backend.getCurrentBGM();
    }

    void AudioSystem::clear(){

        backend.clear();
    }

    void AudioSystem::reloadResources(){

        backend.reloadResources();

    }
}