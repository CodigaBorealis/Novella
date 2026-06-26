#pragma once
#include <optional>
#include <string>
#include "AudioBackend.hpp"

namespace Novella{
/**
 * @class AudioSystem
 * @brief Class responsable for coordinating the audio playback, DOES NOT play the audio, just forwards commands to SFMLAudioBackend
 */
    class AudioSystem{

        public:

        AudioSystem() = delete;

        AudioSystem(ResourceManager& resources);

        ~AudioSystem();
/**
 * @brief adds
 * @param name the alias
 * @param action the action struct to bind to.
 */        
        void play(const std::string& name);

        void stop(const std::string& name);

        void volume(const std::string& name, float volume);

        void pitch(const std::string& name, float pitch);

        void pan(const std::string& name, float pan);
        
        void update();
        
        void clear();
                
        void reloadResources();

        const std::optional<std::string> getCurrentBGM() const;

        private:

        Audio::AudioBackend backend;
    };
}