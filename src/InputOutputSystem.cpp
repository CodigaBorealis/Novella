#include "../Novella/IO/InputOutputSystem.hpp"
#include "../Novella/IO/SceneLoader.hpp"
#include <stdexcept>

namespace Novella::IO{

    void InputOutputSystem::loadSceneFromFile(Engine& engine,const std::filesystem::path& src){

        const std::string extension = src.extension().string();

        if(extension != ".nsc") throw std::runtime_error("Could not load the scene: expected a .nsc file got '" + extension + "'");

        SceneLoader::Loader::load(engine, src);
    }
}