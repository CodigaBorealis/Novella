#pragma once
#include <nlohmann/json.hpp>
#include <nlohmann/json_fwd.hpp>
#include <string>
#include "AudioResource.hpp"
#include "SoundRegistry.hpp"
#include "AudioBackend.hpp"
#include "SoundRegistry.hpp"
#include "Command.hpp"

namespace Novella::Audio {
/**
 * @class AudioSystem
 * @brief Class responsable for coordinating the audio playback, DOES NOT play the audio, just forwards commands to SFMLAudioBackend
 */
    class AudioSystem{

        public:

        AudioSystem();

        ~AudioSystem();
/**
 * @brief adds
 * @param name the alias
 * @param action the action struct to bind to.
 */
        void createResource(const std::string& resourceName, const std::filesystem::path& src, AssetType type);
        
        void play(const std::string& resourceName);

        void stop(const std::string& resourceName);

        void volume(const std::string& resourceName, float volume);

        void pitch(const std::string& resourceName, float pitch);

        void pan(const std::string& resourceName, float pan);
        
        void update();
        
        void clear();
        
        const std::optional<std::string>& getCurrentBgm() const;

        nlohmann::json serialize() const;
        void deserialize(const nlohmann::json& data);

        private:

        void addCommand(Command::Type,unsigned int id, float value);
        std::vector<Command> consume();

        unsigned int nextID();
        unsigned int resolve(const std::string& name);

        std::vector<Command> commands;
        std::unordered_map<std::string, unsigned int> pipeline;
        SoundRegistry assets;
        AudioBackend backend;
        uint32_t next = 0;
        std::optional<std::string> currentBgm;
    };
}