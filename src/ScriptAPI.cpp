#include "../Novella/Scripting/API/ScriptAPI.hpp"
#include "../Novella/Core/Engine.hpp"

namespace Novella::NScript{

    Api::Api(Engine& engine)
        :
        scene(engine.scene()),
        audio(engine.audio()),
        debug(engine.logger()),
        //input(engine.input()),
        layout(engine.layout()),
        renderer(engine.renderer()),
        window(engine.window())
        {}

}