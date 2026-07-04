#include "../Novella/Scripting/API/AudioModule.hpp"
#include "../Novella/Systems/Audio/AudioSystem.hpp"
namespace Novella::NScript::Modules::Audio{

    void play(Runtime::Context& context, const std::string& id){

        context.audio->play(id);
    }

    void stop(Runtime::Context &context, const std::string &id){

        context.audio->stop(id);
    }

    void volume(Runtime::Context &context, const std::string &id, double value){

        context.audio->volume(id, static_cast<float>(value));
    }
}