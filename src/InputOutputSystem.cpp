#include "../Novella/IO/InputOutputSystem.hpp"
#include "../Novella/Scene/Scene.hpp"
#include "../Novella/Attribute/Object.hpp"
#include "../Novella/IO/SceneLoader.hpp"

namespace Novella::IO{

    Scene InputOutputSystem::loadSceneFromFile(Engine& engine,const std::filesystem::path& src){

        return SceneLoader::load(engine, src);
    }
}