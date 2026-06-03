#include "../Novella/Audio/AudioSystem.hpp"
#include <filesystem>
#include <stdexcept>
#include <utility>
namespace Novella::Audio{
    
    AudioSystem::AudioSystem()
        :
        backend(assets)
        {}


    AudioSystem::~AudioSystem(){

        backend.clear();
    }
    
    unsigned int AudioSystem::nextID(){

        return next ++;

    }

    unsigned int AudioSystem::resolve(const std::string& resourceName){

        auto it = pipeline.find(resourceName);

        if(it == pipeline.end()) throw std::runtime_error("AudioSystem::resolve: resource not found:  " + resourceName);

        return it->second;
    }

    void AudioSystem::addCommand(Command::Type type, unsigned int id, float value){

        commands.emplace_back(type, id, value);

    }

    std::vector<Command> AudioSystem::consume(){

        return std::exchange(commands, {});
    }

    void AudioSystem::play(const std::string& resourceName){

        unsigned int resourceID = resolve(resourceName);

        addCommand(Command::Type::Play, resourceID, 0);

        const auto& resource = assets.get(resourceID);

        if(resource.type == AssetType::Music){

            currentBgm = resourceName;
        }
    }

    void AudioSystem::stop(const std::string& resourceName){

        unsigned int resourceID = resolve(resourceName);

        addCommand(Command::Type::Stop, resourceID, 0);

        const auto& resource = assets.get(resourceID);

        if(resource.type == AssetType::Music){

            if(currentBgm == resourceName) currentBgm.reset();
        
        }
    }

    void AudioSystem::volume(const std::string& resourceName, float volume){

        addCommand(Command::Type::SetVolume, resolve(resourceName), volume);
    }

    void AudioSystem::pitch(const std::string& resourceName, float pitch){

        addCommand(Command::Type::SetPitch, resolve(resourceName), pitch);
    }

    void AudioSystem::pan(const std::string& resourceName, float pan){

        addCommand(Command::Type::SetPan, resolve(resourceName), pan);
    }
    
    void AudioSystem::createResource(const std::string& resourceName, const std::filesystem::path& src, AssetType type){
        
        if(!std::filesystem::exists(src)) throw std::runtime_error("AudioSystem::createResource:: ERROR: File not found" + src.string());

        auto extension = src.extension().string();

        AudioResource resource(resourceName, src, type);

        if(pipeline.contains(resource.name)) throw std::runtime_error(resource.name + " Is already a registered key");
                
        resource.id = nextID();
        
        pipeline.emplace(resource.name, resource.id);
        
        assets.registerSound(resource);
    }

    void AudioSystem::update(){

        backend.execute(consume());
        backend.update();
    }

    void AudioSystem::clear(){

        this->commands.clear();
        this->pipeline.clear();
        this->assets.clear();
        this->backend.clear();
        this->next = 0;
    }

    const std::optional<std::string>& AudioSystem::getCurrentBgm() const{

        return currentBgm;

    }
}