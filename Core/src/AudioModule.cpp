#include "Novella/Scripting/API/AudioModule.hpp"
#include "Novella/Scripting/API/DebugModule.hpp"
#include "Novella/Systems/Audio/AudioSystem.hpp"
namespace Novella::NScript::Modules::Audio{

    void play(Runtime::Context& context, const std::string& id){
    
        if(!getCurrentMusic(context).empty()) stopMusic(context);

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

    void setVolume(Runtime::Context &context, const std::string &id, double value){


        context.audio->volume(id, static_cast<float>(value));
    }

    void setPitch(Runtime::Context& context, const std::string& id, double pitch){
        
        
        context.audio->pitch(id, pitch);
    }

    void setPan(Runtime::Context& context, const std::string& id, double pan){
        
        context.audio->pan(id, pan);
    }
    
    std::string getCurrentMusic(Runtime::Context &context){

        auto currentBGM = context.audio->getCurrentBGM();

        if(!currentBGM) return "";

        return currentBGM.value();
    }

    double getMasterVolume(Runtime::Context& context){

        return  static_cast<double>(context.audio->getMasterVolume());
    }

}