#pragma once

namespace Novella{

    class Renderer;
}

namespace Novella::NScript{

    class RendererModule{

        public:

        RendererModule() = delete;

        RendererModule(Renderer& renderer)
        :
        renderer(renderer)
        {}

        private:

        Renderer& renderer;

    };   
}