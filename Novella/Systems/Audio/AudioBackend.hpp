#pragma once
#include <optional>
#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "../Resources/ResourceManager.hpp"

namespace Novella::Audio{

    struct Command;

    class AudioBackend {

        public: 

        AudioBackend() = delete;

        AudioBackend(ResourceManager& resources);
        
        AudioBackend(const AudioBackend&) = delete;

        AudioBackend& operator=(const AudioBackend&) = delete;

        AudioBackend(AudioBackend&&) = delete;
        AudioBackend& operator=(AudioBackend&&) = delete;

        
        ~AudioBackend();
        
        void play(const std::string& name);

        void stop(const std::string& name);

        void volume(const std::string& name, float volume);

        void pitch(const std::string& name, float pitch);

        void pan(const std::string& name, float pan);

        void update();
        void clear();
        
        void reloadResources();
        void loadResources();

        void execute(const std::vector<Command>& commands);

        bool isRegistered(const std::string& name);

        float getMasterVolume() const;

        ::Music& getMusicStream(const std::string& name);
        ::Sound& getSoundStream(const std::string& name);

        const std::optional<std::string> getCurrentBGM() const;
        private:
        
        const ResourceManager::AudioResource& getResource(const std::string& name);
        
        std::unordered_map<std::string, ResourceManager::AudioResource>& resources;

        std::unordered_map<std::string, ::Music> musicStreams;
        std::unordered_map<std::string, ::Sound> soundStreams;

        std::optional<std::string> currentBGM;
};
}
