#include <raylib.h>
#include <vector>
#include <unordered_map>

namespace Novella::Audio {

    class AudioResource;
    class SoundRegistry;
    struct Command;

    class AudioBackend {

        public: 

        AudioBackend() = delete;
        
        AudioBackend(const AudioBackend&) = delete;

        AudioBackend& operator=(const AudioBackend&) = delete;

        AudioBackend(AudioBackend&&) = delete;
        AudioBackend& operator=(AudioBackend&&) = delete;

        AudioBackend(const SoundRegistry& registry);
        
        ~AudioBackend();
        
        void play(const AudioResource& resource);

        void stop(const AudioResource& resource);

        void volume(const AudioResource& resource, float volume);

        void pitch(const AudioResource& resource, float pitch);

        void pan(const AudioResource& resource, float pan);

        void update();
        void clear();

        void execute(const std::vector<Command>& commands);

        private:

        ::Sound& getSound(const AudioResource& asset);

        ::Music& getMusic(const AudioResource& asset);

        const SoundRegistry& registry;
        std::unordered_map<unsigned int, ::Music> musicStreams;
        std::unordered_map<unsigned int, ::Sound> sounds;

};
}
