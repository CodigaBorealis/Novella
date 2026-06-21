#pragma once
#include <string>

namespace Novella{

    class AudioSystem;
}

namespace Novella::NScript{

    class AudioModule{

        public:

        AudioModule() = delete;

        AudioModule(AudioSystem& audio)
            :
            audio(audio)
            {}

        void playSound(const std::string& id);

        void stop(const std::string& id);

        void volume(const std::string& id);

        private:

        AudioSystem& audio;
    }; 
}