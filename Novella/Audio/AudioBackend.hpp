#include "AudioResource.hpp"
#include <raylib.h>

namespace Novella::Audio {

    class AudioBackend {

        public:

        void play(const AudioResource& resource);

        void stop(const AudioResource& resource);

        void volume(const AudioResource& resource, float volume);

        void pitch(const AudioResource& resource, float pitch);

        void pan(const AudioResource& resource, float pan);

        void update();
        void clear();

        private:

        std::unordered_map<unsigned int, ::Music> music;
        std::unordered_map<unsigned int, ::Sound> sounds;
};
}
