#pragma once
#include <filesystem>
#include "../Parser/SceneDefinition.hpp"
#include "ComponentFactory.hpp"

namespace Novella{

    class Engine;
};

namespace Novella::NScript::Runtime{

    struct Context;
}

namespace Novella::NScene::Serialization{

    class Loader{

        public:

        void load(NScript::Runtime::Context& context, const std::filesystem::path& file);

        private:
        
        ComponentFactory factory;

        void build(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);

        void loadResources(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
        void loadObjects(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
        void loadScripts(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
    };

}