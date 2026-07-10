#pragma once
#include <filesystem>
#include "../Parser/SceneDefinition.hpp"

namespace Novella{

    class Engine;
};

namespace Novella::NScript::Runtime{

    struct Context;
}

namespace Novella::NScene::Serialization{

    class Loader{

        public:

        static void load(NScript::Runtime::Context& context, const std::filesystem::path& file);

        private:

        static void build(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);

        static void loadResources(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
        static void loadObjects(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
        static void loadScripts(NScript::Runtime::Context& context, const NScene::Parser::SceneDefinition& scene);
    };

}