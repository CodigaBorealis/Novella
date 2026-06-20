#pragma once

namespace Novella::Rendering{

    class Renderer;
}

namespace Novella::Syntax::NovellaScript::API{

    class RendererModule{

        public:

        RendererModule() = delete;

        RendererModule(Rendering::Renderer& renderer)
        :
        renderer(renderer)
        {}

        private:

        Rendering::Renderer& renderer;

    };   
}