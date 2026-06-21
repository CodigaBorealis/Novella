#pragma once

#include "AudioModule.hpp"
#include "DebugModule.hpp"
#include "InputModule.hpp"
#include "LayoutModule.hpp"
#include "RendererModule.hpp"
#include "SceneModule.hpp"
#include "WindowModule.hpp"

namespace Novella{

    class Engine;
}

namespace Novella::NScript{

    class Api{

        public:

            Api() = delete;

            Api(Engine& engine);

            SceneModule scene;
            AudioModule audio;
            DebugModule debug;
            //InputModule input;
            LayoutModule layout;
            RendererModule renderer;
            WindowModule window;
        };
}