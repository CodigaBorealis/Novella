#include "../Novella/Scripting/API/AudioModule.hpp"
#include "../Novella/Systems/Audio/AudioSystem.hpp"
namespace Novella::NScript::Modules::Audio{

    void play(Runtime::Context& context, const std::string& id){

        context.audio->play(id);
    }

    void stop(Runtime::Context &context, const std::string &id){

        context.audio->stop(id);
    }

    void stopMusic(Runtime::Context& context){

        std::string trackName = getCurrentMusic(context);

        if(trackName.empty()) return;

        context.audio->stop(trackName);
    }

    void volume(Runtime::Context &context, const std::string &id, double value){

        context.audio->volume(id, static_cast<float>(value));
    }

    std::string getCurrentMusic(Runtime::Context &context){

        auto currentBGM = context.audio->getCurrentBGM();

        if(!currentBGM) return "";

        return currentBGM.value();
    }
}