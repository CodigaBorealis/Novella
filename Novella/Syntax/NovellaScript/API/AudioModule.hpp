#pragma once
#include <string>

namespace Novella::Audio{

    class AudioSystem;
}

namespace Novella::Syntax::NovellaScript::API{

    class AudioModule{

        public:

        AudioModule() = delete;

        AudioModule(Audio::AudioSystem& audio)
            :
            audio(audio)
            {}

        void playSound(const std::string& id);

        private:

        Audio::AudioSystem& audio;
    }; 
}