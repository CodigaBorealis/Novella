#pragma once

#include "RuntimeEnvironment.hpp"
namespace Novella::NScript::CoreInitializer{

    void registerWindow(Runtime::RuntimeEnvironment& runtime);
    
    void registerRenderer(Runtime::RuntimeEnvironment& runtime);

    void registerAudio(Runtime::RuntimeEnvironment& runtime);

    void registerScene(Runtime::RuntimeEnvironment& runtime);

    void registerTransform(Runtime::RuntimeEnvironment& runtime);

    void registerLogger(Runtime::RuntimeEnvironment& runtime);

    void registerMath(Runtime::RuntimeEnvironment& runtime);

    void registerString(Runtime::RuntimeEnvironment& runtime);

    void registerFilesystem(Runtime::RuntimeEnvironment& runtime);
    
    void registerInput(Runtime::RuntimeEnvironment& runtime);

    void registerRandomModule(Runtime::RuntimeEnvironment& runtime);

    void registerSpriteModule(Runtime::RuntimeEnvironment& runtime);

    void registerTextModule(Runtime::RuntimeEnvironment& runtime);
    
    void registerUIModule(Runtime::RuntimeEnvironment& runtime);

    void registerObjectModule(Runtime::RuntimeEnvironment& runtime);
    
    void registerOS(Runtime::RuntimeEnvironment& runtime);
}