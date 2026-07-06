#pragma once

#include "RuntimeEnvironment.hpp"
namespace Novella::NScript::CoreInitializer{

    void registerWindow(Runtime::RuntimeEnvironment& runtime);
    
    void registerRenderer(Runtime::RuntimeEnvironment& runtime);

    void registerAudio(Runtime::RuntimeEnvironment& runtime);

    void registerScene(Runtime::RuntimeEnvironment& runtime);

    void registerLayout(Runtime::RuntimeEnvironment& runtime);

    void registerInteraction(Runtime::RuntimeEnvironment& runtime);

    void registerLogger(Runtime::RuntimeEnvironment& runtime);

    void registerMath(Runtime::RuntimeEnvironment& runtime);

    void registerString(Runtime::RuntimeEnvironment& runtime);

    void registerFilesystem(Runtime::RuntimeEnvironment& runtime);
    
    void registerOS(Runtime::RuntimeEnvironment& runtime);
}