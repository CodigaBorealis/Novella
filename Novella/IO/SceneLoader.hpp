#pragma once
#include <filesystem>
#include <string>
#include "../Syntax/Scene/SceneDefinition.hpp"

namespace Novella {

    class Scene;

    class Engine;

    struct Layout;

    enum class Anchor : int;

    enum class SizeMode : int;
};

namespace Novella::Input{

    namespace Keyboard{
        
        enum class Key;

    }

    namespace Mouse{

        enum class Button;
    
    }

}

namespace Novella::SceneLoader{

    class Loader{

        public:

        static void load(Engine& engine, const std::filesystem::path& file);

        private:

        static void build(Engine& engine, const Syntax::Scene::SceneDefinition& scene);

        static void buildObject(Engine& engine, const Syntax::Scene::ObjectDefinition& object);

        static void loadResources(Engine& engine, const Syntax::Scene::SceneDefinition& scene);
        static void loadObjects(Engine& engine, const Syntax::Scene::SceneDefinition& scene);
        static void loadBinds(Engine& engine, const Syntax::Scene::SceneDefinition& scene);

        //static void buildInput(Engine& engine, const Syntax::Scene::InputBindingDefinition& object);

    };

}