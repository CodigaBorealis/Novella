#pragma once
#include <optional>
#include <raylib.h>
#include <unordered_map>
#include <vector>
#include <string>
#include "../Rendering/ResourceManager.hpp"

namespace Novella::Audio {

    struct Command;

    class AudioBackend {

        public: 

        AudioBackend() = delete;

        AudioBackend(Resources::ResourceManager& resources);
        
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

        ::Music& getMusicStream(const std::string& name);
        ::Sound& getSoundStream(const std::string& name);

        const std::optional<std::string> getCurrentBGM() const;
        private:
        
        const Resources::ResourceManager::AudioResource& getResource(const std::string& name);
        
        std::unordered_map<std::string, Resources::ResourceManager::AudioResource>& resources;

        std::unordered_map<std::string, ::Music> musicStreams;
        std::unordered_map<std::string, ::Sound> soundStreams;

        std::optional<std::string> currentBGM;
};
}
