#pragma once
#include <optional>
#include <raylib.h>
#include <vector>
#include <string>

namespace Novella{
    
    class ResourceManager;

    class AudioResource;

    struct Command;

    class AudioSystem {

        public: 

        AudioSystem() = delete;

        AudioSystem(ResourceManager& resources);
        
        AudioSystem(const AudioSystem&) = delete;

        AudioSystem& operator=(const AudioSystem&) = delete;

        AudioSystem(AudioSystem&&) = delete;
        AudioSystem& operator=(AudioSystem&&) = delete;

        
        ~AudioSystem();
        
        void play(const std::string& name);

        void stop(const std::string& name);

        void volume(const std::string& name, float volume);

        void pitch(const std::string& name, float pitch);

        void pan(const std::string& name, float pan);

        void update();

        void execute(const std::vector<Command>& commands);

        float getMasterVolume() const;

        const std::optional<std::string> getCurrentBGM() const;

        private:
        
        AudioResource* getResource(const std::string& name);

        ResourceManager& resources;
        std::optional<std::string> currentBGM;
};
}
