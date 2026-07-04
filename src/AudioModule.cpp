#include "../Novella/Scripting/API/AudioModule.hpp"
#include "../Novella/Systems/Audio/AudioSystem.hpp"
namespace Novella::NScript::Modules::Audio{

    void playSound(Runtime::Context& context, const std::string& id){

        context.audio->play(id);
    }
}