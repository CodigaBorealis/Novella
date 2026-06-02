#pragma once
#include <filesystem>

namespace Novella::Syntax::Scene{

    struct SceneDefinition;
    struct ObjectDefinition;
    struct Property;
};

namespace Novella {

    class Scene;

    class Engine;

    struct Layout;

    enum class Anchor : int;
};


namespace Novella::IO{

    class SceneLoader{

        public:

        static Scene load(Engine& engine, const std::filesystem::path& file);

        private:

        static Scene build(Engine& engine, const Syntax::Scene::SceneDefinition& scene);

        static void buildObject(Engine& engine, const Syntax::Scene::ObjectDefinition& object);

        static int getRenderLayer(const Syntax::Scene::ObjectDefinition& object);

        static Layout getLayout(const Syntax::Scene::ObjectDefinition& object);

        static Anchor getAnchor(const Syntax::Scene::Property* anchorProperty);

        static const Syntax::Scene::Property* findProperty(const Syntax::Scene::ObjectDefinition& object, const std::string& name);

        static std::string getIdentifier(const Syntax::Scene::ObjectDefinition& object, const std::string& name);

        static const Syntax::Scene::ObjectDefinition* findChild(const Syntax::Scene::ObjectDefinition& object, const std::string& name);
    };

}