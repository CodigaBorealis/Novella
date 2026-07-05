#pragma once
#include <string>
#include "../Interpreter/RuntimeContext.hpp"
namespace Novella{

    class AudioSystem;
}

namespace Novella::NScript::Modules::Audio{

        std::string getCurrentMusic(Runtime::Context &context);

        void play(Runtime::Context& context, const std::string& id);

        void stopMusic(Runtime::Context& context);

        void stop(Runtime::Context& context, const std::string& id);

        void volume(Runtime::Context& context, const std::string& id, double value);
}; 
