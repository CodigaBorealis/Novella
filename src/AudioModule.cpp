#include "../Novella/Scripting/API/AudioModule.hpp"
#include "../Novella/Systems/Audio/AudioSystem.hpp"

namespace Novella::NScript{

    void AudioModule::playSound(const std::string& id){

        audio.play(id);
    }
}