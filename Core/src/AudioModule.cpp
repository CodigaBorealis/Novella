#include "../Novella/Scripting/API/AudioModule.hpp"
#include "../Novella/Scripting/API/DebugModule.hpp"
#include "../Novella/Systems/Audio/AudioSystem.hpp"
namespace Novella::NScript::Modules::Audio{

    void play(Runtime::Context& context, const std::string& id){

        if(!isRegistered(context, id)) return;
    
        if(!getCurrentMusic(context).empty()) stopMusic(context);

        context.audio->play(id);
    }

    void stop(Runtime::Context &context, const std::string &id){
        
        if(!isRegistered(context, id)) return;

        context.audio->stop(id);
    }

    void stopMusic(Runtime::Context& context){

        std::string trackName = getCurrentMusic(context);

        if(trackName.empty()) return;

        context.audio->stop(trackName);
    }

    void setVolume(Runtime::Context &context, const std::string &id, double value){

        if(!isRegistered(context, id)){

            return;
        }

        context.audio->volume(id, static_cast<float>(value));
    }

    void setPitch(Runtime::Context& context, const std::string& id, double pitch){
        
        if(!isRegistered(context, id)) return;
        
        context.audio->pitch(id, pitch);
    }

    void setPan(Runtime::Context& context, const std::string& id, double pan){

        if(!isRegistered(context, id)) return;
        
        context.audio->pan(id, pan);
    }

    bool isRegistered(Runtime::Context &context, const std::string &id){

        return context.audio->isRegistered(id);
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