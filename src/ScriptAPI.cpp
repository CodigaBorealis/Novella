#include "../Novella/Syntax/NovellaScript/API/ScriptAPI.hpp"
#include "../Novella/Engine.hpp"

namespace Novella::Syntax::NovellaScript::API{

    ScriptAPI::ScriptAPI(Engine& engine)
        :
        scene(engine.scene()),
        audio(engine.audio()),
        debug(engine.logger()),
        input(engine.input()),
        layout(engine.layout()),
        renderer(engine.renderer()),
        window(engine.window())
        {}

}