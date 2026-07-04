#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
namespace Novella{

    class AudioSystem;
}

namespace Novella::NScript::Modules::Audio{

        void playSound(Runtime::Context& context, const std::string& id);

        void stop(Runtime::Context& context, const std::string& id);

        void volume(Runtime::Context& context, const std::string& id);
}; 
