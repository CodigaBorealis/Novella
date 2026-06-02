#pragma once
#include "FileReader.hpp"
#include <filesystem>

namespace Novella{

    class Scene;
    class Engine;
}

namespace Novella::Syntax::Scene {

    struct SceneDefinition;
}

namespace Novella::IO{

    class InputOutputSystem{

        public:
        
        Scene loadSceneFromFile(Engine& engine, const std::filesystem::path& src);

        private:
        
        FileReader reader;

    };

}