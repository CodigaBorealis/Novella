#pragma once
#include <filesystem>
#include "../Parser/SceneDefinition.hpp"

namespace Novella{

    class Engine;
};

namespace Novella::NScene::Serialization{

    class Loader{

        public:

        static void load(Engine& engine, const std::filesystem::path& file);

        private:

        static void build(Engine& engine, const NScene::Parser::SceneDefinition& scene);

        static void buildObject(Engine& engine, const NScene::Parser::ObjectDefinition& object);

        static void loadResources(Engine& engine, const NScene::Parser::SceneDefinition& scene);
        static void loadObjects(Engine& engine, const NScene::Parser::SceneDefinition& scene);
        static void loadScripts(Engine& engine, const NScene::Parser::SceneDefinition& scene);
    };

}