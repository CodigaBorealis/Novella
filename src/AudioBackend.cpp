#include "../Novella/Audio/AudioBackend.hpp"
#include <raylib.h>
#include <stdexcept>

namespace Novella::Audio{

    AudioBackend::AudioBackend(const SoundRegistry& registry):
        registry(registry){

            ::InitAudioDevice();
            
        }

    AudioBackend::~AudioBackend(){

        clear();
        ::CloseAudioDevice();

    }

    ::Music& AudioBackend::getMusic(const AudioResource& asset){

        auto it = musicStreams.find(asset.id);

        if(it != musicStreams.end()){

            return it->second;
        }

        auto [insertedIt, inserted] = musicStreams.try_emplace(asset.id, ::LoadMusicStream(asset.src.string().c_str()));

        if(insertedIt->second.ctxData == nullptr) throw std::runtime_error("Failed to load music: " + asset.name);

        return insertedIt->second;
    }

    ::Sound& AudioBackend::getSound(const AudioResource& asset){

        auto it = sounds.find(asset.id);

        if(it == sounds.end()){

            return it->second;
        }

        auto [insertedIt, inserted] = sounds.try_emplace(asset.id, ::LoadSound(asset.src.string().c_str()));

        if(insertedIt->second.stream.buffer == nullptr) throw std::runtime_error("Failed to load sound: " + asset.name);

        return insertedIt->second;
    }

    void AudioBackend::play(const AudioResource& asset){

        if(asset.type == AssetType::Music){

            auto& music = getMusic(asset);

            if(music.ctxData == nullptr) throw std::runtime_error("nolkkldaljkdakjlda");
            ::PlayMusicStream(music);

        }else{

            auto& sound = getSound(asset);

            ::PlaySound(sound);
        }
    }

    void AudioBackend::stop(const AudioResource& asset){

        if(asset.type == AssetType::Music){

            auto& music = getMusic(asset);

            ::StopMusicStream(music);

        }else{

            auto& sound = getSound(asset);

            ::StopSound(sound);
        }
    }

    void AudioBackend::volume(const AudioResource& asset, float volume){
        
        if(asset.type == AssetType::Music){

            auto& music = getMusic(asset);

            ::SetMusicVolume(music, volume);

        }else{

            auto& sound = getSound(asset);

            ::SetSoundVolume(sound, volume);
        }
    }

    void AudioBackend::pitch(const AudioResource& asset, float volume){

        if(asset.type == AssetType::Music){

            auto& music = getMusic(asset);

            ::SetMusicPitch(music, volume);

        }else{

            auto& sound = getSound(asset);

            ::SetSoundPitch(sound, volume);
        }        
    }

    void AudioBackend::pan(const AudioResource& asset, float volume){

        if(asset.type == AssetType::Music){

            auto& music = getMusic(asset);

            ::SetMusicPan(music, volume);

        }else{

            auto& sound = getSound(asset);

            ::SetSoundPan(sound, volume);
        }        
    }

    void AudioBackend::execute(const std::vector<Command>& commands){

        for(const auto& command: commands){

            if(!registry.contains(command.id)) continue;

            const AudioResource& asset = registry.get(command.id);//?????

            switch (command.type){

                case Command::Play:{

                    play(asset);

                    break;
                }

                case Command::Stop:{

                    stop(asset);

                    break;
                }

                case Command::SetVolume:{

                    volume(asset, command.value);
                    break;
                }

                case Command::SetPitch:{

                    pitch(asset, command.value);
                    break;
                }

                case Command::SetPan:{

                    pan(asset, command.value);
                    break;
                }

                default:

                break;

            }
        }

    }

    void AudioBackend::update(){

        for(auto& [id, music] : musicStreams){

            ::UpdateMusicStream(music);

        }

    }

    void AudioBackend::clear(){

        for(auto& [id, sound] : sounds){

            ::UnloadSound(sound);
        }

        for(auto& [id, music] : musicStreams){

            ::UnloadMusicStream(music);
        }

        this->musicStreams.clear();
        this->sounds.clear();
    }
}